#pragma once
#include <iostream>
#include <optional>
#include <string>

#include "TicketMachine.h"

#include "StrongID.h"

#include "log.h"

class Car {
public:
  Car(const std::string &registrationMark);

  Car() = delete;

  void takeTicket(TicketMachine & ticketMachine);

  std::optional<std::reference_wrapper<const TicketID>>
  giveTicket(void) const;

  const std::string &registrationMark(void) const;


  void binTicket(void);

private:
  std::string registrationMark_;
  std::optional<TicketID> ticket_;
};
