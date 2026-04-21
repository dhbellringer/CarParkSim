#include "RegistrationIndex.h"

bool RegistrationIndex::addAssociation(const RegistrationMark& registrationMark, const AccountID& accountID) {

  if (registrationToAccountMap_.contains(registrationMark)) {
    return false; // Registration mark already associated with an account
  }
  auto [it, inserted] = registrationToAccountMap_.emplace(registrationMark, accountID);
  return true;
}

std::optional<AccountID> RegistrationIndex::getAccountID(const RegistrationMark& registrationMark) const {
  auto it = registrationToAccountMap_.find(registrationMark);
  if (it != registrationToAccountMap_.end()) {
    return it->second;
  }
  return std::nullopt; // No account associated with this registration mark
}

void RegistrationIndex::deleteAssociation(const RegistrationMark& registrationMark) {
  registrationToAccountMap_.erase(registrationMark);
}
