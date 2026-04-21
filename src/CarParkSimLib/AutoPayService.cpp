#include "StrongID.h"
#include "AutoPayService.h"
#include "PaymentCalculatorFactory.h"

AutoPayService::AutoPayResult AutoPayService::attemptAutoPay(const SessionID& session, const RegistrationMark& registrationMark)
{
  auto sessionDetails = sessionManager_.getSession(session);
  if (!sessionDetails) {

    return AutoPayResult::NoSession;
  }
  if (!sessionDetails->get().is_active()) {
    return AutoPayResult::SessionNotActive;
  }
  auto accountID = registrationIndex_.getAccountID(registrationMark);
  if (!accountID) {
    return AutoPayResult::NoAccount;
  }
  auto account = accountManager_.getCustomerAccount(*accountID);
  if (!account) {
    return AutoPayResult::NoAccount;
  }

  PaymentCalculatorFactory calculatorFactory;
  auto paymentCalc = calculatorFactory.createPaymentCalculator();

  double sessionPayment = paymentCalc->calculate(*sessionDetails);

  if (!paymentService_.makePayment(account->get().getPaymentDetails(), sessionPayment)) {
    return AutoPayResult::PaymentFailed;
  }

  sessionDetails->get().markPaid(std::chrono::system_clock::now());
  return AutoPayResult::Success;
}
