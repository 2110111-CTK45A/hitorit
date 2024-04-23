#include "DiscreteSpace/Shape.hpp"
#include "doctest.h"

// DEFINITION
template<std::size_t N>
auto DiscreteSpace::Shape<N>::cbegin() const {
	return axes.cbegin();
}

template<std::size_t N>
auto DiscreteSpace::Shape<N>::cend() const {
	return axes.cend();
}

template<std::size_t N>
std::size_t DiscreteSpace::Shape<N>::get_rank() const {
	return axes.size();
}

// IMPLEMENTATION

// UNIT TEST
TEST_CASE("Shape Instantiation") {
	DiscreteSpace::Shape a((uint32_t)1);
	DiscreteSpace::Shape b{1, 2};
	DiscreteSpace::Shape<3> c(11, 20, 4);
	DiscreteSpace::Shape d;

	CHECK(a.get_length(0) == 1);
	CHECK(b.get_rank() == 2);
	CHECK(c.get_rank() == 3);
	CHECK(c.get_max_length() == 20);
	CHECK(d.get_length(0) == 0);
}

TEST_CASE("Shape Index Projection") {
	DiscreteSpace::Shape<3> a{4, 3, 3};
	CHECK(a.get_projection(0, 6) == 2);
	CHECK(a.get_projection(1, 6) == 1);
	CHECK(a.get_projection(2, 6) == 0);
}
