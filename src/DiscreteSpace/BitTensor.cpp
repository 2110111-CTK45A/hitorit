#include "DiscreteSpace/BitTensor.hpp"
#include "doctest.h"

// DEFINITION

// UNIT TEST
TEST_CASE("BitTensor Instantiation") {
	// Default constructor
	DiscreteSpace::Shape<3> a(2, 3, 4);
	DiscreteSpace::BitTensor<3> b(a);
	boost::dynamic_bitset<> c(24);
	auto tensor = b.get_tensor();
	CHECK(b.get_shape()->get_length(0) == 2);
	CHECK(*tensor == c);
	CHECK(tensor->size() == 24);
	// Copy constructor
	DiscreteSpace::BitTensor<3> bb(b);
	CHECK(*b.get_tensor() == *bb.get_tensor());
	CHECK(&*b.get_tensor() != &*bb.get_tensor());
}
