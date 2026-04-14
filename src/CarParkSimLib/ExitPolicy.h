#pragma once

#include "ParkingSession.h"
#include <chrono>

class ExitPolicy {
public:
  enum class ExitPolicyResult { Allowed, NotPaid, GraceExceeded };

  template <typename Rep, typename Period>
  explicit ExitPolicy(const std::chrono::duration<Rep, Period> &gracePeriod)
      : gracePeriod_(
            std::chrono::duration_cast<std::chrono::seconds>(gracePeriod)) {}

  ExitPolicy() = delete;

  ExitPolicyResult exitAllowed(const ParkingSession &session) const;

private:
  std::chrono::seconds gracePeriod_;
};

