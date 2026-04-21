#include "CustomerAccountManager.h"

CustomerAccount& CustomerAccountManager::createCustomerAccount(const PaymentDetails& paymentDetails) {
  AccountID newAccountID(UUIDv4::generate());
  auto [it, ok] = accounts_.emplace(newAccountID, CustomerAccount(newAccountID, paymentDetails));
  if (!ok) {
    throw std::logic_error("Cannot create customer account: Account ID already exists");
  }
  return it->second;
}

std::optional<std::reference_wrapper<CustomerAccount>> CustomerAccountManager::getCustomerAccount(const AccountID& accountID) {
  auto it = accounts_.find(accountID);
  if (it == accounts_.end()) {
    return std::nullopt;
  }
  return it->second;
}
