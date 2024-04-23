#ifndef DISCRETESPACE_TENSOR_HPP
#define DISCRETESPACE_TENSOR_HPP

#include <cstdint>
#include <concepts>
#include <boost/dynamic_bitset.hpp>

#include "DiscreteSpace/Shape.hpp"
#include "DiscreteSpace/ShapeAggregate.hpp"

namespace DiscreteSpace {

/** Abstract class for tensors */
template<typename T, std::size_t N>
class Tensor : public ShapeAggregate<N> {
public:
// LIFECYCLE
	/** Constructor from shape
	
	Only uses ShapeAggregate's default constructor
	@param shape The reference of the shape for the tensor
	*/
	Tensor(const Shape<N>& shape);

	/** Copy constructor
	@param from The reference from which values are copied to this object
	*/
	Tensor(const Tensor<T, N>& from);

	/** Virtual destructor
	
	Compiler-generated
	*/
	//virtual ~Tensor();
	
// ACCESS
	/** Tensor getter
	@return A constant pointer to the tensor of the object
	*/
	const T* get_tensor() const;

protected:
	/** The shape of the tensor */
	using ShapeAggregate<N>::shape;
	/** The values in the tensor */
	T tensor;

// OPERATIONS
	/** Pure virtual tensor creation helper method */
	virtual void init_tensor() = 0;
};

// INLINE METHODS
template<typename T, std::size_t N>
Tensor<T, N>::Tensor(const Shape<N>& shape) : ShapeAggregate<N>(shape) {}

template<typename T, std::size_t N>
Tensor<T, N>::Tensor(const Tensor<T, N>& from) {
	shape = from.shape;
	tensor = from.tensor;
}

template<typename T, std::size_t N>
const T* Tensor<T, N>::get_tensor() const {
	return &tensor;
}

}

#endif // DISCRETESPACE_TENSOR_HPP
