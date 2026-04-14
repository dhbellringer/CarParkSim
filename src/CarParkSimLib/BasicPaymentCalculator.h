#pragma once

#include "IPaymentCalculator.h"

class BasicPaymentCalculator : public IPaymentCalculator {
  // Inherited via IPaymentCalculator
  double calculate(const ParkingSession &session) override;
};
