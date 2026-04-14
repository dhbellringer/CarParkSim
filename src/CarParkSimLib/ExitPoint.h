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

class CarPark;

class ExitPoint {
public:
	ExitPoint(ParkingSessionManager& sessionManager, AutoSessionService& anprService,
		TicketManager& ticketManager, ExitPolicy& exitPolicy);
	bool attemptExit(const Car& car);

private:
	struct ResolvedSession {
		SessionID sessionID;
		bool usedANPR;
		std::string registrationMark;
	};
	std::optional<ResolvedSession>
		resolveSession(const Car& car);
	bool attemptSessionExit(const SessionID& sessionID);
	Barrier barrier_;
	Display display_;
	ANPRCamera camera_;
	ParkingSessionManager& sessionMananger_;
	AutoSessionService& anprService_;
	TicketManager& ticketManager_;
	ExitPolicy& exitPolicy_;
};
