#include <iostream>
#include "CarPark.h"
#include "log.h"

CarPark::CarPark(int maxSessions)
    : sessionManager_(maxSessions), exitPolicy_(std::chrono::seconds(60)),
      entry_(sessionManager_, anprService_, ticketManager),
      exit_(sessionManager_, anprService_, ticketManager, exitPolicy_),
      paymentMachine_(paymentService_, sessionManager_, ticketManager) {}

bool CarPark::enter(Car &car) {
  log2("CP", "Car is approaching entrance");
  return entry_.carDetected(car);
}

bool CarPark::exit(Car &car) {
  log2("CP", "Car is approaching exit");
  return exit_.attemptExit(car);
}

bool CarPark::pay(Car &car) {
  auto ticket = car.giveTicket();
  if (ticket) {
  return paymentMachine_.payTicket(*ticket, {"Blah"});
  }
  std::cout << "DRIVER DOESN'T HAVE A TICKET";
  return false;
}
