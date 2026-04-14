#pragma once
#include "IPaymentCalculator.h"

class PaymentCalculatorFactory {
  public:
  std::unique_ptr<IPaymentCalculator> createPaymentCalculator() const;
  };
