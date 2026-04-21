#pragma once

#include <map>
#include <optional>
#include "StrongID.h"

class AutoSessionService {
public:
  void associate(const RegistrationMark &registrationMark, const SessionID &sessionID);
  std::optional<std::reference_wrapper<const SessionID>> lookupRegistrationMark(const RegistrationMark &registrationMark) const;
  void invalidate(const RegistrationMark &registrationMark);

private:
  std::map<RegistrationMark, SessionID> internal_map_;
};
