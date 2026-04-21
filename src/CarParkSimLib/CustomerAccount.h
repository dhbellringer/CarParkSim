#pragma once

#include <string>
#include <optional>
#include "StrongID.h"
#include "PaymentDetails.h"

class CustomerAccount {
public:
  CustomerAccount(const AccountID& accountID, const PaymentDetails& paymentDetails) : accountID_(accountID), paymentDetails_(paymentDetails) {}
  CustomerAccount() = delete;

  const AccountID& getAccountID() const { return accountID_; }
  const PaymentDetails& getPaymentDetails() const { return paymentDetails_; }
private:
  AccountID accountID_;
  PaymentDetails paymentDetails_;
};
