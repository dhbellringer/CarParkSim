#include <catch2/catch_test_macros.hpp>
#include <CarParkSimLib/AutoSessionService.h>

TEST_CASE("AutoSessionService associates a registration mark with a session") {
  AutoSessionService svc;

  RegistrationMark rm("ABC123");
  SessionID sid("S1");

  svc.associate(rm, sid);

  auto result = svc.lookupRegistrationMark(rm);
  REQUIRE(result.has_value());
  REQUIRE(result->get() == sid);
}

TEST_CASE("AutoSessionService throws on duplicate association") {
  AutoSessionService svc;

  RegistrationMark rm("ABC123");
  SessionID sid1("S1");
  SessionID sid2("S2");

  svc.associate(rm, sid1);

  REQUIRE_THROWS_AS(svc.associate(rm, sid2), std::logic_error);
}

TEST_CASE("AutoSessionService returns nullopt for unknown registration mark") {
  AutoSessionService svc;

  RegistrationMark rm("UNKNOWN");

  auto result = svc.lookupRegistrationMark(rm);
  REQUIRE_FALSE(result.has_value());
}

TEST_CASE("AutoSessionService invalidates an association") {
  AutoSessionService svc;

  RegistrationMark rm("ABC123");
  SessionID sid("S1");

  svc.associate(rm, sid);

  // sanity check
  REQUIRE(svc.lookupRegistrationMark(rm).has_value());

  svc.invalidate(rm);

  auto result = svc.lookupRegistrationMark(rm);
  REQUIRE_FALSE(result.has_value());
}

TEST_CASE("AutoSessionService invalidate is safe on unknown registration mark") {
  AutoSessionService svc;

  REQUIRE_NOTHROW(svc.invalidate(RegistrationMark("DOES_NOT_EXIST")));
}
