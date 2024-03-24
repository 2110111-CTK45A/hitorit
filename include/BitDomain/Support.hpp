#ifndef BitDomain_Support_HPP
#define BitDomain_Support_HPP

#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <cstdint>

namespace BitDomain {

template <typename S = std::size_t>
class Support {
//private:
	//template <typename T = uint8_t>
	//constexpr bool bit_flip(S axis, T index) {
		//domains[axis] ^= boost::dynamic_bitset<>(1 << index);
		//return domains[axis][index];
	//}

protected:
	std::vector<boost::dynamic_bitset<>> domains = std::vector<boost::dynamic_bitset<>>();

public:
	template <typename T = uint8_t, typename... Ns>
	explicit Support(Ns... n) {
		T domainSize[sizeof...(n)] = {n...};
		for (S i = 0; i < sizeof...(n); ++i) {
			domains.push_back(boost::dynamic_bitset<>(domainSize[i]));
		}
	}

	constexpr S get_dimension() const;

	boost::dynamic_bitset<> get_axis(S axis) const;
};

}

#endif
