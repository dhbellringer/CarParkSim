#include "ParkingSessionManager.h"
#include "UUIDv4.h"

ParkingSessionManager::ParkingSessionManager(std::size_t maxSessions)
	: maxSessions_(maxSessions) {
}

ParkingSession& ParkingSessionManager::startSession(
	const ANPRReading& anprReading,
	const std::chrono::system_clock::time_point& now) {

	SessionID newSessionID("");
	do {
		newSessionID = SessionID(UUIDv4::generate());
	} while (active_.contains(newSessionID));

	if (active_.contains(newSessionID)) {
		throw std::logic_error(
			"Cannot start session: Session already started for this ticket ID");
	}

	auto [it, ok] = active_.emplace(
		newSessionID, ParkingSession(newSessionID, anprReading, now));
	if (!ok) {
		throw std::logic_error("Cannot start session");
	}
	return it->second;
}

std::optional<std::reference_wrapper<ParkingSession>>
ParkingSessionManager::getSession(const SessionID& sessionID) {
	auto it = active_.find(sessionID);
	if (it != active_.end()) {
		return it->second;
	}
	return std::nullopt;
}

std::optional<std::reference_wrapper<const ParkingSession>>
ParkingSessionManager::getSession(const SessionID& sessionID) const {
	auto it = active_.find(sessionID);
	if (it != active_.end()) {
		return it->second;
	}
	return std::nullopt;
}

void ParkingSessionManager::endSession(const SessionID& sessionID) {
	auto it = active_.find(sessionID);
	if (it != active_.end()) {
		archive_.emplace(sessionID, it->second);
		active_.erase(it);
	}
	else {
		throw std::logic_error("Cannot end session: Session doesn't exist");
	}
}

bool ParkingSessionManager::isFull() const {
	return active_.size() >= maxSessions_;
}
