#include "TicketMachine.h"

TicketMachine::PrintTicketResult TicketMachine::printTicket(const TicketID& ticketID) {
  if (currentTicket_) {
    return PrintTicketResult::TicketAlreadyPrinted;
  }

  if (ticketsLeft_ == 0) {
    return PrintTicketResult::OutOfTickets;
  }

  // if (jammed) {
  //   return CreateTicketResult::Jammed;
  // }
  currentTicket_ = ticketID;
  ticketsLeft_--;
  return PrintTicketResult::Success;
}

TicketID TicketMachine::takeTicket() {
  if (!currentTicket_) {
    throw std::logic_error("Cannot take ticket, no ticket currently generated");
  }
  TicketID ticket = *currentTicket_;
  currentTicket_ = std::nullopt;
  return ticket;
}


void TicketMachine::load(std::size_t tickets) { ticketsLeft_ += tickets; }
