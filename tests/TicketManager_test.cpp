#include <catch2/catch_test_macros.hpp>
#include <CarParkSimLib/TicketManager.h>
#include <CarParkSimLib/StrongID.h>

// A simple fake SessionID for testing
static SessionID makeSession(int n) {
    return SessionID(std::to_string(n));
}

TEST_CASE("TicketManager creates a ticket for a session") {
    TicketManager tm;

    SessionID sid = makeSession(1);
    TicketID tid = tm.createTicketForSession(sid);

    REQUIRE(tid.value.empty() == false);
}

TEST_CASE("TicketManager associates ticket with correct session") {
    TicketManager tm;

    SessionID sid = makeSession(42);
    TicketID tid = tm.createTicketForSession(sid);

    auto result = tm.lookupSessionForTicket(tid);

    REQUIRE(result.has_value());
    REQUIRE(result.value() == sid);
}

TEST_CASE("TicketManager returns nullopt for unknown ticket") {
    TicketManager tm;

    TicketID unknown("does-not-exist");

    auto result = tm.lookupSessionForTicket(unknown);

    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("TicketManager generates unique ticket IDs") {
    TicketManager tm;

    SessionID sid1 = makeSession(1);
    SessionID sid2 = makeSession(2);

    TicketID t1 = tm.createTicketForSession(sid1);
    TicketID t2 = tm.createTicketForSession(sid2);

    REQUIRE(t1 != t2);
}

TEST_CASE("TicketManager can store multiple tickets") {
    TicketManager tm;

    SessionID sid1 = makeSession(10);
    SessionID sid2 = makeSession(20);
    SessionID sid3 = makeSession(30);

    TicketID t1 = tm.createTicketForSession(sid1);
    TicketID t2 = tm.createTicketForSession(sid2);
    TicketID t3 = tm.createTicketForSession(sid3);

    REQUIRE(tm.lookupSessionForTicket(t1).value() == sid1);
    REQUIRE(tm.lookupSessionForTicket(t2).value() == sid2);
    REQUIRE(tm.lookupSessionForTicket(t3).value() == sid3);
}
