#pragma once

#include <string>

template <typename Tag>
struct StrongID {
	std::string value;

	explicit StrongID(std::string v) : value(std::move(v)) {}

	StrongID(const StrongID&) = default;
	StrongID(StrongID&&) noexcept = default;
	StrongID& operator=(const StrongID&) = default;
	StrongID& operator=(StrongID&&) noexcept = default;

	friend bool operator==(StrongID const& a, StrongID const& b) {
		return a.value == b.value;
	}
	friend bool operator<(StrongID const& a, StrongID const& b) {
		return a.value < b.value;
	}
};


struct SessionIDTag {};
struct TicketIDTag {};
struct AccountIDTag {};

using SessionID = StrongID<SessionIDTag>;
using TicketID = StrongID<TicketIDTag>;
using AccountID = StrongID<AccountIDTag>;
