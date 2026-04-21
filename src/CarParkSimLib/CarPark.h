#pragma once

#include "AutoSessionService.h"
#include "Car.h"
#include "EntryPoint.h"
#include "ExitPoint.h"
#include "ParkingSessionManager.h"
#include "ExitPolicy.h"
#include "TicketManager.h"
#include "PaymentMachine.h"
#include "RegistrationIndex.h"
#include "CustomerAccountManager.h"

class CarPark {
public:
  CarPark(int maxSessions, RegistrationIndex &registrationIndex, CustomerAccountManager &accountManager);
  ;
  bool enter(Car &car);
  bool exit(Car &car);
  bool pay(Car &car);
  ;

private:
  // Keeps track of parking sessions, both active and archived. Responsible for starting and ending sessions.
  ParkingSessionManager sessionManager_;
  // Keeps track of associations between registration marks and customer accounts.
  RegistrationIndex &registrationIndex_;
  // Responsible for managing customer accounts.
  CustomerAccountManager &accountManager_;
  // Responsible for managing associations between tickets and parking sessions.
  TicketManager ticketManager;
  // Responsible for managing associations between registration marks and parking sessions.
  AutoSessionService anprService_;
  // Responsible for processing payments.
  PaymentService paymentService_;
  // Responsible for managing the auto payment process at exit.
  AutoPayService autoPayService_;
  // Responsible for determining whether a session is allowed to exit.
  ExitPolicy exitPolicy_;
  // Responsible for managing the payment machine.
  PaymentMachine paymentMachine_;
  // Responsible for managing the entry point of the car park.
  EntryPoint entry_;
  // Responsible for managing the exit point of the car park.
  ExitPoint exit_;

};
