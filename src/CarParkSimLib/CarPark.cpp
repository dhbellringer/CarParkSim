#include <iostream>
#include "CarPark.h"
#include "log.h"

CarPark::CarPark(int maxSessions, RegistrationIndex& registrationIndex, CustomerAccountManager& accountManager)
  : sessionManager_(maxSessions)
  , exitPolicy_(std::chrono::seconds(60))
  , autoPayService_(sessionManager_, accountManager, registrationIndex, paymentService_)
  , entry_(sessionManager_, anprService_, ticketManager)
  , exit_(sessionManager_, anprService_, autoPayService_, ticketManager, exitPolicy_)
  , paymentMachine_(paymentService_, sessionManager_, ticketManager)
  , registrationIndex_(registrationIndex)
  , accountManager_(accountManager) 
{
}

bool CarPark::enter(Car& car) {
  log2("CP", "Car is approaching entrance");
  return entry_.carDetected(car);
}

bool CarPark::exit(Car& car) {
  log2("CP", "Car is approaching exit");
  return exit_.attemptExit(car);
}

bool CarPark::pay(Car& car) {
  auto ticket = car.giveTicket();
  if (ticket) {
    return paymentMachine_.payTicket(*ticket, { "Blah" });
  }
  std::cout << "DRIVER DOESN'T HAVE A TICKET";
  return false;
}
