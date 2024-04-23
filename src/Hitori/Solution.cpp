#include "Hitori/Solution.hpp"
#include "doctest.h"

// DEFINITION
template<std::size_t N>
bool Hitori::Solution<N>::set_cell(const std::integral auto index, const bool value) {
	bool currentValue = tensor[index];
	tensor[index] = value;
	return currentValue != value;
}

template<std::size_t N>
std::string Hitori::Solution<N>::to_string() {
	std::string str = "";
	std::size_t maxIndex = 1;
	for (std::size_t i = 0; i < shape->get_length(1); ++i) {
		for (std::size_t j = 0; j < shape->get_length(0); ++j) {
			if (tensor[shape->get_index(i,j)]) {
				str.append("1");
			} else {
				str.append("0");
			}
		}
		str.append("\n");
	}
	return str;
}

// UNIT TEST
TEST_CASE("Solution Instantiation") {
	// Default constructor
	DiscreteSpace::Shape<2> a(9, 2);
	Hitori::Solution<2> s(a);
	// Copy constructor
	Hitori::Solution<2> m(s);

	CHECK(s.to_string() == "000000000\n000000000\n");
}

