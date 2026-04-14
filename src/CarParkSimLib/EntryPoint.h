#pragma once

#include "ParkingSessionManager.h"
#include "ANPRCamera.h"
#include "AutoSessionService.h"
#include "Barrier.h"
#include "Car.h"
#include "TicketMachine.h"
#include "TicketManager.h"


#include "Display.h"

class EntryPoint {
public:
  EntryPoint(ParkingSessionManager &sessionManager, AutoSessionService &anprService, TicketManager &ticketManager);

  bool carDetected(Car &car);

private:
  Barrier barrier_;
  Display display_;
  TicketMachine ticketMachine_;
  ANPRCamera camera_;
  ParkingSessionManager &sessionManager_;
  AutoSessionService &anprService_;
  TicketManager &ticketManager_;
};
