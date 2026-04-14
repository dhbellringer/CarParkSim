#pragma once

#include "AutoSessionService.h"
#include "Car.h"
#include "EntryPoint.h"
#include "ExitPoint.h"
#include "ParkingSessionManager.h"
#include "ExitPolicy.h"
#include "TicketManager.h"
#include "PaymentMachine.h"

class CarPark {
public:
  CarPark(int maxSessions);
  ;
  bool enter(Car &car);
  bool exit(Car &car);
  bool pay(Car &car);
  ;

private:
  ParkingSessionManager sessionManager_;
  TicketManager ticketManager;
  AutoSessionService anprService_;
  PaymentService paymentService_;
  ExitPolicy exitPolicy_;
  PaymentMachine paymentMachine_;
  EntryPoint entry_;
  ExitPoint exit_;
};
