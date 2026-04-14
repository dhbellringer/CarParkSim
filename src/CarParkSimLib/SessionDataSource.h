#pragma once

#include <optional>
#include <unordered_map>
#include "ParkingSession.h"

class ISessionDataSource {
public:
  virtual ~ISessionDataSource() = default;

  virtual void save(const ParkingSession &session) = 0;
  virtual std::optional<ParkingSession> load(const std::string &ticketID) = 0;
};

class VirtualSessionDataSource : public ISessionDataSource {

  void save(const ParkingSession &session) override {
    auto it = database_.find(session.ticketID);
    if (it == database_.end()) {
      database_[session.ticketID] = session;
    }
  }

  std::optional<ParkingSession> load(const std::string &ticketID) override {
    auto it = database_.find(ticketID);
    if (it == database_.end()) {
      return std::nullopt;
    }
    return 
  }

private:
  std::unordered_map<std::string, ParkingSession> database_;
};