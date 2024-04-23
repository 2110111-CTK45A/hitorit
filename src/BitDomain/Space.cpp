#include "BitDomain/Space.hpp"
#include "doctest.h"

// DEFINITIONS
template <typename S>
BitDomain::Space<S>::Space(Support<S>* support) {
	this->support = support;
	S size = 1;
	for (S i = 0; i < support->get_rank(); ++i) {
		size *= support->get_axis_size(i);
	}
	bitspace = boost::dynamic_bitset<>(size);
}


// CLASS IMPLEMENTATIONS
template class BitDomain::Space<uint8_t>;
template class BitDomain::Space<int8_t>;
template class BitDomain::Space<uint16_t>;
template class BitDomain::Space<int16_t>;
template class BitDomain::Space<uint32_t>;
template class BitDomain::Space<int32_t>;
template class BitDomain::Space<uint64_t>;
template class BitDomain::Space<int64_t>;

// UNIT TESTS
TEST_CASE("Space Constructor") {
	BitDomain::Support<int> a(3, 6);
	BitDomain::Space<int> b(&a);
}

TEST_CASE("0D Space") {
	BitDomain::Support<uint8_t> a;
	BitDomain::Space<uint8_t> b(&a);
}
