#ifndef BITDOMAIN_SPACE_HPP
#define BITDOMAIN_SPACE_HPP

#include "BitDomain/Support.hpp"

#include <cstdint>
#include <cmath>

namespace BitDomain {

template <typename S = std::size_t>
class Space {
private:
	Support<S>* support;
	boost::dynamic_bitset<> bitspace;
public:
	// CONSTRUCTOR
	explicit Space(Support<S>* support);

	// DESTRUCTOR
	//virtual ~Space();
	
	// GETTER
	//template <typename T = uint64_t, typename... Ns>
	//explicit CoordinateDomain(Ns... n) {
		//return 0;
	//}
};

}

#endif
