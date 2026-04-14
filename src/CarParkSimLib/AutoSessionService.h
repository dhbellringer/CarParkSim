#pragma once

#include <map>
#include <optional>
#include "StrongID.h"

class AutoSessionService {
public:
  void associate(const std::string &registrationMark,
                 const SessionID &sessionID);

  std::optional<std::reference_wrapper<const SessionID>> 
  lookupRegistrationMark(const std::string &registrationMark) const;

  void invalidate(const std::string &registrationMark);

private:
  std::map<std::string, SessionID> internal_map_;
};
