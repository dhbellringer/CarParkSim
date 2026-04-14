#include "EntryPoint.h"
#include "ANPRReading.h"

EntryPoint::EntryPoint(ParkingSessionManager &sessionManager,
                       AutoSessionService &anprService,
                       TicketManager &ticketManager)
    : sessionManager_(sessionManager), camera_(0.5), anprService_(anprService),
      display_("## ENTRY ##"), ticketManager_(ticketManager) {
  ticketMachine_.load(50);
}

bool EntryPoint::carDetected(Car &car) {
  if (sessionManager_.isFull()) {
    display_.showMessage("Car park is full - sorry!!");
    return false;
  }

  display_.showMessage("Welcome - attempting ANPR");

  ANPRReading result = camera_.readRegistrationMark(car);

  ParkingSession & sessionID = sessionManager_.startSession(result,
                               std::chrono::system_clock::now());

;
  if (result.Result == ANPRResult::Success) {
    display_.showMessage("Registration mark read successfully");
    anprService_.associate(result.RegistrationMark, SessionID(sessionID.sessionID()));
  }

  TicketID ticketID = ticketManager_.createTicketForSession(sessionID.sessionID());
  ticketMachine_.printTicket(ticketID);

  display_.showMessage("Please take ticket");
  car.takeTicket(ticketMachine_);

  display_.showMessage("Opening barrier");
  barrier_.open();
  display_.showMessage("Barrier open, please enter");
  display_.showMessage("Closing barrier");
  barrier_.close();
  display_.showMessage("Barrier closed");
  return true;
}
