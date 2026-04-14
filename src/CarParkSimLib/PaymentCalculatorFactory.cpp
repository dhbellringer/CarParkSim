#include "PaymentCalculatorFactory.h"
#include "BasicPaymentCalculator.h"

std::unique_ptr<IPaymentCalculator>
PaymentCalculatorFactory::createPaymentCalculator() const {
  return std::make_unique<BasicPaymentCalculator>();
}
