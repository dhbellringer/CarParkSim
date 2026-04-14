#include "ExitPolicy.h"


ExitPolicy::ExitPolicyResult ExitPolicy::exitAllowed(const ParkingSession &session) const {
  auto paid = session.paid_at();
  if (!paid) {
    return ExitPolicyResult::NotPaid;
  }
  if (std::chrono::system_clock::now() - *paid > gracePeriod_) {
    return ExitPolicyResult::GraceExceeded;
  }
  return ExitPolicyResult::Allowed;
}
