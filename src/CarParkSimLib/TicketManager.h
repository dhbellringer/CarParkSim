#pragma once
#include <string>
#include <map>
#include <optional>
#include "StrongID.h"

class TicketManager {
public:
  TicketID createTicketForSession(const SessionID &sessionID);
  std::optional<SessionID> lookupSessionForTicket(const TicketID &ticketID) const;

private:
  std::map<TicketID, SessionID> ticketLookup_;
};