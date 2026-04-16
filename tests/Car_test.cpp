#include <catch2/catch_test_macros.hpp>
#include <CarParkSimLib/Car.h>
#include <CarParkSimLib/TicketMachine.h>
#include <CarParkSimLib/StrongID.h>



TEST_CASE("Car stores and returns registration mark") {
	Car c("ABC123");
	REQUIRE(c.registrationMark() == "ABC123");
}

TEST_CASE("Car starts without a ticket") {
	Car c("ABC123");
	REQUIRE_FALSE(c.giveTicket().has_value());
}

TEST_CASE("Car takes a ticket from the ticket machine") {
	TicketID tid{ "BLAH" };
	TicketMachine machine;

	Car c("ABC123");
	machine.load(1);
	machine.printTicket(tid);
	c.takeTicket(machine);

	auto ticket = c.giveTicket();
	REQUIRE(ticket.has_value());
	REQUIRE(ticket->get() == tid);
}

TEST_CASE("Car bins its ticket") {
	TicketID tid{ "BLAH" };
	TicketMachine machine;

	Car c("ABC123");
	machine.load(1);
	machine.printTicket(tid);
	c.takeTicket(machine);

	REQUIRE(c.giveTicket().has_value());

	c.binTicket();
	REQUIRE_FALSE(c.giveTicket().has_value());
}


TEST_CASE("Car throws if tried to bins its ticket with no ticket") {

	Car c("ABC123");

	REQUIRE_THROWS_AS(c.binTicket(), std::logic_error);
}

TEST_CASE("Car throws if it tries to take a ticket from an empty machine") {
	TicketMachine machine;

	Car c("ABC123");
	REQUIRE_THROWS_AS(c.takeTicket(machine), std::logic_error);
}