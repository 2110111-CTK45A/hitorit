#ifndef DISCRETESPACE_SUBDOMAIN_HPP
#define DISCRETESPACE_SUBDOMAIN_HPP

#include <boost/dynamic_bitset.hpp>
#include <cstdint>
#include <concepts>
#include <valarray>

namespace DiscreteSpace {

/** Array of bitsets for one dimension of a domain

#include "DiscreteSpace/SubDomain.hpp" --llib
*/
class SubDomain {
private:
	std::valarray<boost::dynamic_bitset<>> domain;
public:
// LIFECYCLE
	/** Constructor from size and length
	@param size The number of bitsets
	@param length The size of each bitset
	*/
	explicit SubDomain(const std::integral auto size, const std::integral auto length);

	/** Copy constructor
	@param from The value to copy to this object
	*/
	SubDomain(const SubDomain& from);

	//virtual ~SubDomain();
	
// ACCESS
	/** Domain getter
	@param index The domain number (counting from 0) to get
	@return A constant pointer to the specified domain
	*/
	template<std::integral T>
	const boost::dynamic_bitset<>* get_domain(const T index) const;
};

// INLINE METHODS
SubDomain::SubDomain(const std::integral auto size, const std::integral auto length) {
	domain = std::valarray<boost::dynamic_bitset<>>(boost::dynamic_bitset<>(length), size);
}

}

#endif // DISCRETESPACE_SUBDOMAIN_HPP
