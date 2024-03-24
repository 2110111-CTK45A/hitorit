#ifndef BitDomain_Space_HPP
#define BitDomain_Space_HPP

#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <cstdint>

namespace HitoriGenerator {

template <typename S = std::size_t>
class Space {
private:
	Support<S>* support;
	boost::dynamic_bitset<> bitspace;
public:
	//template <typename T = uint64_t>
	//T get_projection(S axis, T index) {
		
	//}
	//template <typename T = uint64_t, typename... Ns>
	//explicit CoordinateDomain(Ns... n) {
		//return 0;
	//}

};

}

#endif
