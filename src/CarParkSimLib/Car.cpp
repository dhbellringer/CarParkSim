#include "Car.h"
#include "log.h"

Car::Car(const RegistrationMark& registrationMark, bool is_auto_payer)
	: registrationMark_(registrationMark), is_auto_payer_(is_auto_payer), ticket_(std::nullopt) {
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
		return;
	}
	throw std::logic_error("Can't bin ticket, no ticket to discard");
}

const RegistrationMark& Car::registrationMark(void) const {
	log3("CAR", "Registration mark read", registrationMark_.value);
	return registrationMark_;
}
