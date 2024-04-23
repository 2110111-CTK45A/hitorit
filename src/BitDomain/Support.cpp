#include "BitDomain/Support.hpp"
#include "doctest.h"

// DEFINITIONS
template <typename S>
void BitDomain::Support<S>::add_axis(S size) {
	domain.push_back(boost::dynamic_bitset<>(size));
}

template <typename S>
void BitDomain::Support<S>::del_axis() {
	domain.pop_back();
}

template <typename S>
void BitDomain::Support<S>::del_axis(S axis) {
	domain.erase(domain.begin() + axis);
}

template <typename S>
S BitDomain::Support<S>::get_rank() const {
	return domain.size();
}

template <typename S>
boost::dynamic_bitset<> BitDomain::Support<S>::get_axis(const S axis) const {
	return domain[axis];
}

template <typename S>
S BitDomain::Support<S>::get_axis_size(const S axis) const {
	return domain[axis].size();
}

template <typename S>
std::vector<S> BitDomain::Support<S>::get_shape() const {
	std::vector<S> v;
	for (S i = 0; i < get_rank(); ++i) {
		v.push_back(get_axis_size(i));
	}
	return v;
}

// CLASS IMPLEMENTATIONS
template class BitDomain::Support<uint8_t>;
template class BitDomain::Support<int8_t>;
template class BitDomain::Support<uint16_t>;
template class BitDomain::Support<int16_t>;
template class BitDomain::Support<uint32_t>;
template class BitDomain::Support<int32_t>;
template class BitDomain::Support<uint64_t>;
template class BitDomain::Support<int64_t>;

// UNIT TESTS
TEST_CASE("Support Constructor") {
	BitDomain::Support<int> a{3, 6};

	boost::dynamic_bitset<> b(3);
	CHECK(a.get_axis(0) == b);
}

TEST_CASE("Support Getter") {
	BitDomain::Support<uint8_t> a((uint8_t)10, (uint8_t)12);
	boost::dynamic_bitset<> b(10);
	auto c = a.get_axis(0);

	CHECK(c == b);

	c.flip();
	CHECK(c != b);

	CHECK(a.get_rank() == 2);
	CHECK(a.get_axis_size(0) == 10);
	CHECK(a.get_axis_size(1) == 12);

	auto d = std::vector<uint8_t>{10, 12};
	CHECK(a.get_shape()[0] == d[0]);
	CHECK(a.get_shape()[1] == d[1]);
}

TEST_CASE("0D Support") {
	BitDomain::Support<uint8_t> a;
	CHECK(a.get_rank() == 0);
}

TEST_CASE("Support Projection") {
	BitDomain::Support<int> a(4, 3, 2);

	CHECK(a.get_projection(0, 6) == 2);
	CHECK(a.get_projection(1, 6) == 2);
	CHECK(a.get_projection(2, 6) == 1);
}
