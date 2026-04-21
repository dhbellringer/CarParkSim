#pragma once

#include "CustomerAccount.h"
#include "UUIDv4.h"
#include <map>

class CustomerAccountManager {
public:
  CustomerAccount& createCustomerAccount(const PaymentDetails & paymentDetails);

  std::optional<std::reference_wrapper<CustomerAccount>> getCustomerAccount(const AccountID &accountID);
private:
  std::map<AccountID, CustomerAccount> accounts_;
};
