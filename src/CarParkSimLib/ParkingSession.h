#pragma once

#include <chrono>
#include "ANPRReading.h"
#include "StrongID.h"

class ParkingSession {

public:
  explicit ParkingSession(
      const SessionID &sessionID, const ANPRReading &anprReading,
      const std::chrono::system_clock::time_point &entryTime)
      : sessionID_(sessionID), anprReading_(anprReading),
        entryTimestamp_(entryTime), state_(State::Active) {}

  ParkingSession() = delete;

  void markPaid(const std::chrono::system_clock::time_point &paymentTime) {
    if (state_ == State::Active) {
      state_ = State::Paid;
      paymentTimestamp_ = paymentTime;
      return;
    } else {
      throw std::logic_error("Cannot mark paid: Session is not active");
    }
  }

  void markExit(const std::chrono::system_clock::time_point &exitTime) {
    if (state_ == State::Paid) {
      state_ = State::Exited;
      exitTimestamp_ = exitTime;
      return;
    } else if (state_ == State::Exited) {
      throw std::logic_error("Cannot mark exited: Session already exited");
    } else if (state_ == State::Active) {
      throw std::logic_error("Cannot mark exited: Session not paid");
    }
  }

  const ANPRReading &anprReading() const noexcept { return anprReading_; }

  const SessionID &sessionID() const noexcept { return sessionID_; }

  const std::chrono::system_clock::time_point started_at() const {
    return entryTimestamp_;
  }

  std::optional<std::chrono::system_clock::time_point> paid_at() const {
    if (is_paid()) {
      return paymentTimestamp_;
    }
    return std::nullopt;
  }

  std::optional<std::chrono::system_clock::time_point> exit_at() const {
    if (is_exited()) {
      return exitTimestamp_;
    }
    return std::nullopt;
  }

  bool is_paid() const noexcept {
    return (state_ == State::Paid || state_ == State::Exited);
  }

  bool is_exited() const noexcept { return (state_ == State::Exited); }

  bool is_active() const noexcept { return state_ == State::Active; }

private:
  enum class State { Active, Paid, Exited };

  SessionID sessionID_;
  ANPRReading anprReading_;
  std::chrono::system_clock::time_point entryTimestamp_;
  std::chrono::system_clock::time_point paymentTimestamp_;
  std::chrono::system_clock::time_point exitTimestamp_;
  State state_;
};
