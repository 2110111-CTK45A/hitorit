#ifndef DISCRETESPACE_SHAPEAGGREGATE_HPP
#define DISCRETESPACE_SHAPEAGGREGATE_HPP

#include <cstdint>
#include <concepts> // std::integral

#include "DiscreteSpace/Shape.hpp"

namespace DiscreteSpace {

/** Abstract class for objects which need to hold a const pointer to a shape

#include "DiscreteSpace/ShapeAggregate.hpp"
*/
template<std::size_t N>
class ShapeAggregate {
public:
// LIFECYCLE
	/** Default constructor
	Compiler-generated
	*/
	ShapeAggregate() = default;

	/** Constructor from shape
	@param shape The reference of the shape for the object
	*/
	explicit ShapeAggregate(const Shape<N>& shape);

	/** Pure virtual destructor
	@attention Does not destroy shape
	*/
	virtual ~ShapeAggregate() = 0;

// ACCESS
	/** Shape getter
	@return A constant pointer to shape
	*/
	const Shape<N>* get_shape() const;

protected:
	const Shape<N>* shape;
};

// INLINE METHODS
template<std::size_t N>
ShapeAggregate<N>::ShapeAggregate(const Shape<N>& shape) {
	this->shape = &shape;
}

template<std::size_t N>
ShapeAggregate<N>::~ShapeAggregate() {}

template<std::size_t N>
const Shape<N>* ShapeAggregate<N>::get_shape() const {
	return shape;
}

}

#endif // DISCRETESPACE_SHAPEAGGREGATE_HPP
