#pragma once

#include "PaymentDetails.h"

class PaymentService {
public:
  bool makePayment(const PaymentDetails &paymentDetails, double amount);

private:
};