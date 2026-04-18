#include <stdexcept>
#include "AutoSessionService.h"

void AutoSessionService::associate(const std::string& registrationMark,
  const SessionID& sessionID) {
  if (!internal_map_.emplace(registrationMark, sessionID).second) {
    throw std::logic_error("ANPR Service: Association already exists");
  }
}

std::optional<std::reference_wrapper<const SessionID>>
AutoSessionService::lookupRegistrationMark(
  const std::string& registrationMark) const {
  auto it = internal_map_.find(registrationMark);

  if (it != internal_map_.end()) {
    return it->second;
  }
  return std::nullopt;
}

void AutoSessionService::invalidate(const std::string& registrationMark) {
  internal_map_.erase(registrationMark);
}
