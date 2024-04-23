#ifndef DISCRETESPACE_DOMAIN_HPP
#define DISCRETESPACE_DOMAIN_HPP

#include <cstdint>
#include <concepts>
#include <vector>

#include "DiscreteSpace/Shape.hpp"
#include "DiscreteSpace/ShapeAggregate.hpp"
#include "DiscreteSpace/SubDomain.hpp"

namespace DiscreteSpace {

/** Domain of values for tensor by axis */
template<std::size_t N>
class Domain : public ShapeAggregate<N> {
public:
// LIFECYCLE
	/** Constructor from shape
	
	Only uses ShapeAggregate's default constructor
	@param shape The reference of the shape for the domain
	*/
	explicit Domain(const Shape<N>& shape);

	/** Virtual destructor */
	//virtual ~Domain();

// ACCESS
	/** SubDomain getter
	@param axis The axis (counting from 0) of the subdomain get
	@return A constant pointer to the specified subdomain
	*/
	template<std::integral T>
	const SubDomain* get_subdomain(const T axis) const;
private:
	using ShapeAggregate<N>::shape;
	std::vector<SubDomain> subdomains;

// OPERATIONS
	void init_subdomains();
};

}

#endif // DISCRETESPACE_DOMAIN_HPP
