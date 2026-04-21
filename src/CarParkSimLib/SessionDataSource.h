#pragma once

#include <optional>
#include <unordered_map>
#include "StrongID.h"
#include "ParkingSession.h"

class ISessionDataSource {
public:
  virtual ~ISessionDataSource() = default;

  virtual void save(const ParkingSession &session) = 0;
  virtual std::optional<ParkingSession> load(const SessionID &sessionID) = 0;
};

class VirtualSessionDataSource : public ISessionDataSource {

  void save(const ParkingSession &session) override {
    auto it = database_.find(session.sessionID());
    if (it == database_.end()) {
      database_[session.sessionID()] = session;
    }
  }

  std::optional<ParkingSession> load(const SessionID &sessionID) override {
    auto it = database_.find(sessionID);
    if (it == database_.end()) {
      return std::nullopt;
    }
    return it->second;
  }

private:
  std::unordered_map<SessionID, ParkingSession> database_;
};