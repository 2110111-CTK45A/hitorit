#include "DiscreteSpace/SubDomain.hpp"
#include "doctest.h"

// DEFINITION

DiscreteSpace::SubDomain::SubDomain(const DiscreteSpace::SubDomain& from) {
	domain = from.domain;
}

template<std::integral T>
const boost::dynamic_bitset<>* DiscreteSpace::SubDomain::get_domain(const T index) const {
	return &domain[index];
}

// IMPLEMENTATION

// UNIT TEST
TEST_CASE("SubDomain Instantiation") {
	DiscreteSpace::SubDomain a(1, 1);
	boost::dynamic_bitset<> b(1);
	CHECK(*a.get_domain(0) == b);
}
