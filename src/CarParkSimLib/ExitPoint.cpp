#include "ExitPoint.h"

ExitPoint::ExitPoint(ParkingSessionManager& sessionManager
  , AutoSessionService& anprService
  , AutoPayService& autoPayService
  , TicketManager& ticketManager
  , ExitPolicy& exitPolicy
)
  : sessionManager_(sessionManager)
  , camera_(0.5)
  , anprService_(anprService)
  , exitPolicy_(exitPolicy)
  , display_("## EXIT ##")
  , ticketManager_(ticketManager)
  , autoPayService_(autoPayService)
{
}

bool ExitPoint::attemptExit(const Car& car) {
  auto sessionResolution = resolveSession(car);
  if (!sessionResolution) {
    return false;
  }

  // If the session is "active" (i.e. not paid), then attempt to autopay
  auto session = sessionManager_.getSession(sessionResolution->sessionID);
  if (session && session->get().is_active()) {
    // If ANPR succeeds at exit, then use that
    // If ANPR fails at exit, BUT succeeded at entry, then use the ANPR result from entry to attempt autopay and session exit
    std::optional<RegistrationMark> registrationMark;
    if (sessionResolution->usedANPR) { // We have the registration mark available from the exit ANPR attempt, so use that
      registrationMark = sessionResolution->registrationMark;
    }
    else { // Otherwise, see if we can use the ANPR result from entry (if it succeeded) to attempt autopay
      if (session->get().anprReading().Result_ == ANPRResult::Success) {
        registrationMark = session->get().anprReading().RegistrationMark_;
      }
    }

    if (registrationMark) {
      auto success = autoPayService_.attemptAutoPay(sessionResolution->sessionID, *registrationMark);
      switch (success)
      {
      case AutoPayService::AutoPayResult::Success:
        display_.showMessage("Payment successful");
        break;
      case AutoPayService::AutoPayResult::PaymentFailed:
        display_.showMessage("Payment failed");
        break;
      case AutoPayService::AutoPayResult::NoAccount:
        display_.showMessage("No account for this registration mark");
        break;
      case AutoPayService::AutoPayResult::NoSession:
        display_.showMessage("No session details");
        break;
      case AutoPayService::AutoPayResult::SessionNotActive:
        display_.showMessage("Session already paid!!");
        break;
      }
    }
  }
  // At this point, either the session was already paid, or we attempted autopay (if it was active) so attempt exit as normal
  bool exitAllowed = attemptSessionExit(sessionResolution->sessionID);

  if (exitAllowed && sessionResolution->usedANPR) {
    anprService_.invalidate(sessionResolution->registrationMark);
  }
  return exitAllowed;
}

std::optional<ExitPoint::ResolvedSession>
ExitPoint::resolveSession(const Car& car) {
  display_.showMessage("Welcome - attempting ANPR");
  ANPRReading result = camera_.readRegistrationMark(car);

  // Try ANPR
  if (result.Result_ == ANPRResult::Success) {
    display_.showMessage(
      "Registration mark read successfully, looking for associated session");

    // Is there a session for this Registration Mark?
    auto foundSession =
      anprService_.lookupRegistrationMark(result.RegistrationMark_);
    if (foundSession) {
      display_.showMessage("Session found");
      return ResolvedSession{ *foundSession, true, result.RegistrationMark_ };
    }
    else {
      display_.showMessage("No session found for registration mark read at exit");
      display_.showMessage("Please insert ticket");
    }
  }
  else {
    display_.showMessage("ANPR failed to read registration mark");
    display_.showMessage("Please insert ticket");
  }

  auto ticket = car.giveTicket();
  if (!ticket) {
    display_.showMessage("No ticket inserted");
    return std::nullopt;
  }
  auto foundSession = ticketManager_.lookupSessionForTicket(*ticket);

  if (!foundSession) {
    display_.showMessage("Invalid ticket");
    return std::nullopt;
  }

  display_.showMessage("Session found from ticket");

  return ResolvedSession{ *foundSession, false, RegistrationMark{""} };
}

bool ExitPoint::attemptSessionExit(const SessionID& sessionID) {

  auto session = sessionManager_.getSession(sessionID);
  if (session) {
    auto exitStatus = exitPolicy_.exitAllowed(*session);
    if (exitStatus == ExitPolicy::ExitPolicyResult::Allowed) {
      display_.showMessage("Thank you, barrier opening");
      barrier_.open();
      display_.showMessage("Barrier open, please exit");
      sessionManager_.endSession(sessionID);
      display_.showMessage("Barrier closing");
      barrier_.close();
      return true;
    }
    else if (exitStatus == ExitPolicy::ExitPolicyResult::NotPaid) {
      display_.showMessage("Ticket is unpaid, please pay at a payment machine");
      return false;
    }
    else if (exitStatus == ExitPolicy::ExitPolicyResult::GraceExceeded) {
      display_.showMessage("Exit time after grace period, please make a "
        "further payment at a payment machine");
      return false;
    }
  }

  return false;
}
