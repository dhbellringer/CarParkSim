#pragma once

#include <optional>
#include "UUIDv4.h"
#include "StrongID.h"

class TicketMachine {
public:
  enum class PrintTicketResult {
    Success
    , TicketAlreadyPrinted
    , PrinterJammed
    , OutOfTickets
  };
  PrintTicketResult printTicket(const TicketID& ticketID);
  TicketID takeTicket();
  void load(std::size_t tickets);

private:
  std::optional<TicketID> currentTicket_ = std::nullopt;
  std::size_t ticketsLeft_ = 0;
};
