#pragma once

#include "ParkingSessionManager.h"
#include "ANPRCamera.h"
#include "AutoSessionService.h"
#include "Barrier.h"
#include "Car.h"
#include "ExitPolicy.h"
#include "Display.h"
#include "TicketManager.h"
#include "StrongID.h"
#include "CustomerAccountManager.h"
#include "RegistrationIndex.h"
#include "AutoPayService.h"

class CarPark;

class ExitPoint {
public:
  ExitPoint(
    ParkingSessionManager& sessionManager
    , AutoSessionService& anprService
    , AutoPayService& autoPayService
    , TicketManager& ticketManager
    , ExitPolicy& exitPolicy);
  bool attemptExit(const Car& car);

private:
  struct ResolvedSession {
    SessionID sessionID;
    bool usedANPR;
    RegistrationMark registrationMark;
  };
  std::optional<ResolvedSession> resolveSession(const Car& car);
  bool attemptSessionExit(const SessionID& sessionID);
  bool attemptAutoPay(const SessionID& session, const RegistrationMark& registrationMark);

  Barrier barrier_;
  Display display_;
  ANPRCamera camera_;
  ParkingSessionManager& sessionManager_;
  AutoSessionService& anprService_;
  TicketManager& ticketManager_;
  ExitPolicy& exitPolicy_;
  AutoPayService& autoPayService_;
};
