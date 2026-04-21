#pragma once

#include <map>
#include <string>
#include <optional>
#include "StrongID.h"


class RegistrationIndex {
public:
  bool addAssociation(const RegistrationMark& registrationMark, const AccountID& accountID);

  std::optional<AccountID> getAccountID(const RegistrationMark& registrationMark) const;

  void deleteAssociation(const RegistrationMark & registrationMark);
private:
  std::map<RegistrationMark, AccountID> registrationToAccountMap_;
};