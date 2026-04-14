#include "Car.h"
#include "log.h"

Car::Car(const std::string& registrationMark)
	: registrationMark_(registrationMark), ticket_(std::nullopt) {
}

void Car::takeTicket(TicketMachine& ticketMachine) {
	ticket_ = ticketMachine.takeTicket();
}

std::optional<std::reference_wrapper<const TicketID>>
Car::giveTicket(void) const {
	if (!ticket_) {
		return std::nullopt;
	}
	else {
		return std::cref(*ticket_);
	}
}

void Car::binTicket(void) {
	if (ticket_) {
		ticket_ = std::nullopt;
	}
	throw std::logic_error("Can't bin ticket, no ticket to discard");
}

const std::string& Car::registrationMark(void) const {
	log3("CAR", "Registration mark read", registrationMark_);
	return registrationMark_;
}
