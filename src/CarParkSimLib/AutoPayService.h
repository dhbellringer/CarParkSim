#pragma once

#include "ParkingSessionManager.h"
#include "CustomerAccountManager.h"
#include "RegistrationIndex.h"
#include "PaymentService.h"

class AutoPayService
{
public:
  enum class AutoPayResult
  {
    Success
    , PaymentFailed
    , NoAccount
    , NoSession
    , SessionNotActive
  };
  AutoPayService(ParkingSessionManager& sessionManager, CustomerAccountManager& accountManager, RegistrationIndex& registrationIndex, PaymentService& paymentService)
    : sessionManager_(sessionManager)
    , accountManager_(accountManager)
    , registrationIndex_(registrationIndex)
    , paymentService_(paymentService) { }
  AutoPayService() = delete;
  AutoPayResult attemptAutoPay(const SessionID& session, const RegistrationMark& registrationMark);
private:
  ParkingSessionManager& sessionManager_;
  CustomerAccountManager& accountManager_;
  RegistrationIndex& registrationIndex_;
  PaymentService& paymentService_;
};