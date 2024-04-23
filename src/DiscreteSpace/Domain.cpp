#include "DiscreteSpace/Domain.hpp"
#include "doctest.h"

// DEFINITION
template<std::size_t N>
DiscreteSpace::Domain<N>::Domain(const DiscreteSpace::Shape<N>& shape) : DiscreteSpace::ShapeAggregate<N>(shape) {
	init_subdomains();
}

template<std::size_t N>
template<std::integral T>
const DiscreteSpace::SubDomain* DiscreteSpace::Domain<N>::get_subdomain(const T axis) const {
	return &subdomains[axis];
}

template<std::size_t N>
void DiscreteSpace::Domain<N>::init_subdomains() {
	std::size_t length = shape->get_max_length();
	for (std::size_t i = 0; i < shape->get_rank(); ++i) {
		subdomains.push_back(DiscreteSpace::SubDomain(shape->get_length(i), length));
	}
}

// IMPLEMENTATION

// UNIT TEST
TEST_CASE("Domain Instantiation") {
	DiscreteSpace::Shape<2> a(2, 3);
	DiscreteSpace::Domain<2> b(a);
	DiscreteSpace::SubDomain c(2, 3);
	CHECK(b.get_shape()->get_length(0) == 2);
	CHECK(b.get_subdomain(0)->get_domain(0)->size() == 3);
}
