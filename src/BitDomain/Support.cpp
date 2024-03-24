#include "BitDomain/Support.hpp"
#include "TestCommon.hpp"

// DEFINITIONS
template <typename S>
constexpr S BitDomain::Support<S>::get_dimension() const {
	return domains.size();
}

template <typename S>
boost::dynamic_bitset<> BitDomain::Support<S>::get_axis(S axis) const {
	return domains[axis];
}


// CLASS IMPLEMENTATIONS
template class BitDomain::Support<uint8_t>;

// UNIT TESTS
TEST_CASE("Testing Support's constructor and encapsulation") {
	BitDomain::Support<uint8_t> a((uint8_t)10, (uint8_t)12);

	boost::dynamic_bitset<> b(10);
	auto c = a.get_axis(0);

	CHECK(c == b);

	c.flip();

	CHECK(c != b);
	CHECK(a.get_axis(0) == b);
}

TEST_CASE("0D Support") {
	BitDomain::Support<uint8_t> a;
	CHECK(a.get_dimension() == 0);
}
