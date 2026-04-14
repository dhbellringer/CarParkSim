#pragma once
#include "ParkingSession.h"

class IPaymentCalculator {
public:
  virtual ~IPaymentCalculator() = default;
  virtual double calculate(const ParkingSession &session) = 0;
};