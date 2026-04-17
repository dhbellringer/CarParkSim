#include "TicketManager.h"
#include "UUIDv4.h"

TicketID
TicketManager::createTicketForSession(const SessionID &sessionID) {

  TicketID newTicket(UUIDv4::generate());
  while (ticketLookup_.contains(newTicket)) {
      newTicket = TicketID(UUIDv4::generate());
  }
  ticketLookup_.emplace(newTicket, sessionID);
  return newTicket;
}

std::optional<SessionID>
TicketManager::lookupSessionForTicket(const TicketID &ticketID) const {
  auto it = ticketLookup_.find(ticketID);
  if (it != ticketLookup_.end()) {
    return it->second;
  }

  return std::nullopt;
}
