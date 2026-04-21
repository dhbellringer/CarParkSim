#pragma once
#include <optional>
#include <string>

#include "TicketMachine.h"
#include "StrongID.h"

class Car {
public:
  Car(const RegistrationMark& registrationMark, bool is_auto_payer);

  Car() = delete;

  void takeTicket(TicketMachine& ticketMachine);

  std::optional<std::reference_wrapper<const TicketID>> giveTicket(void) const;

  const RegistrationMark& registrationMark(void) const;

  bool is_auto_payer() const noexcept { return is_auto_payer_; }

  void binTicket(void);

private:
  RegistrationMark registrationMark_;
  bool is_auto_payer_;
  std::optional<TicketID> ticket_;
};
