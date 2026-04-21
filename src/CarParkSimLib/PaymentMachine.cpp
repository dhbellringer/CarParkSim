#include "PaymentMachine.h"
#include "PaymentCalculatorFactory.h"

PaymentMachine::PaymentMachine(PaymentService &paymentService,
                               ParkingSessionManager &parkingSessionManager,
                               TicketManager &ticketManager)
    : paymentService_(paymentService),
      parkingSessionManager_(parkingSessionManager),
      ticketManager_(ticketManager), display_("PYT") {}

bool PaymentMachine::payTicket(const TicketID &ticket,
                               const PaymentDetails &paymentDetails) {

  auto sessionID = ticketManager_.lookupSessionForTicket(ticket);
  if (!sessionID) {
    display_.showMessage("Invalid ticket, please seek assistance");
    return false;
  }

  auto sessionFound = parkingSessionManager_.getSession(*sessionID);
  if (!sessionFound) {
    display_.showMessage("Parking session for this ticket cannot be found, "
                         "please seek assistance");
    return false;
  }

  ParkingSession &session = sessionFound->get();

  if (!session.is_active()) {
    display_.showMessage("The parking session for this ticket is not active, "
                         "please seek assistance");
    return false;
  }

  PaymentCalculatorFactory calculatorFactory;
  auto paymentCalc = calculatorFactory.createPaymentCalculator();

  double sessionPayment = paymentCalc->calculate(session);
  std::string message = std::format("Please pay £{:.2f}", sessionPayment);
  display_.showMessage(message);

  if (paymentService_.makePayment(paymentDetails, sessionPayment)) {
    session.markPaid(std::chrono::system_clock::now());
    return true;
  }
  display_.showMessage("Payment failed, please try again.");
  return false;
}
