#pragma once

#include <chrono>
#include <map>
#include <optional>
#include "ParkingSession.h"
#include "StrongID.h"

class ParkingSessionManager {
public:
  ParkingSessionManager(std::size_t maxSessions);

  ParkingSession & startSession(const ANPRReading &anprReading,
               const std::chrono::system_clock::time_point &now);

  std::optional<std::reference_wrapper<ParkingSession>>
  getSession(const SessionID &sessionID);

  std::optional<std::reference_wrapper<const ParkingSession>>
  getSession(const SessionID &sessionID) const;

  void endSession(const SessionID& sessionID);

  bool isFull() const;

private:
  std::size_t maxSessions_;
  std::map<SessionID, ParkingSession> active_;
  std::map<SessionID, ParkingSession> archive_;
};
