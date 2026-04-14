#pragma once

#include "PaymentDetails.h"
#include "PaymentService.h"
#include "ParkingSessionManager.h"
#include "TicketManager.h"
#include "Display.h"
#include "StrongID.h"

class PaymentMachine {
public:
  PaymentMachine(PaymentService &paymentService, ParkingSessionManager & parkingSessionManager, TicketManager & ticketManager);
  PaymentMachine() = delete;

  bool payTicket(const TicketID &ticket,
                 const PaymentDetails &paymentDetails);

private:
  Display display_;
  PaymentService &paymentService_;
  ParkingSessionManager &parkingSessionManager_;
  TicketManager &ticketManager_;
};
