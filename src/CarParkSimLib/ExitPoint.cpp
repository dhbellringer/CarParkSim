#include "ExitPoint.h"
#include "ANPRReading.h"
#include "CarPark.h"
#include <string>

ExitPoint::ExitPoint(ParkingSessionManager &sessionManager,
                     AutoSessionService &anprService,
                     TicketManager &ticketManager, ExitPolicy &exitPolicy)
    : sessionMananger_(sessionManager), camera_(0.5), anprService_(anprService),
      exitPolicy_(exitPolicy), display_("## EXIT ##"),
      ticketManager_(ticketManager) {}

bool ExitPoint::attemptExit(const Car &car) {
  auto sessionResolution = resolveSession(car);
  if (!sessionResolution) {
    return false;
  }

  bool exitAllowed = attemptSessionExit(sessionResolution->sessionID);

  if (exitAllowed && sessionResolution->usedANPR) {
    anprService_.invalidate(sessionResolution->registrationMark);
  }
  return exitAllowed;
  }

std::optional<ExitPoint::ResolvedSession>
ExitPoint::resolveSession(const Car &car) {
  display_.showMessage("Welcome - attempting ANPR");
  ANPRReading result = camera_.readRegistrationMark(car);

  // Try ANPR
  if (result.Result == ANPRResult::Success) {
    display_.showMessage(
        "Registration mark read successfully, looking for associated session");

    // Is there a session for this Registration Mark?
    auto foundSession =
        anprService_.lookupRegistrationMark(result.RegistrationMark);
    if (foundSession) {
      display_.showMessage("Session found");
      return ResolvedSession{*foundSession, true, result.RegistrationMark};
    }
  }
  display_.showMessage("Please insert ticket");

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

  display_.showMessage("Session found");

  return ResolvedSession{*foundSession, false, ""};
}

bool ExitPoint::attemptSessionExit(const SessionID &sessionID) {

  auto session = sessionMananger_.getSession(sessionID);
  if (session) {
    auto exitStatus = exitPolicy_.exitAllowed(*session);
    if (exitStatus == ExitPolicy::ExitPolicyResult::Allowed) {
      display_.showMessage("Thank you, barrier opening");
      barrier_.open();
      display_.showMessage("Barrier open, please exit");
      sessionMananger_.endSession(sessionID);
      display_.showMessage("Barrier closing");
      barrier_.close();
      return true;
    } else if (exitStatus == ExitPolicy::ExitPolicyResult::NotPaid) {
      display_.showMessage("Ticket is unpaid, please pay at a payment machine");
      return false;
    } else if (exitStatus == ExitPolicy::ExitPolicyResult::GraceExceeded) {
      display_.showMessage("Exit time after grace period, please make a "
                           "further payment at a payment machine");
      return false;
    }
  }

  return false;
}
