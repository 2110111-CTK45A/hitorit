#ifndef DISCRETESPACE_BITTENSOR_HPP
#define DISCRETESPACE_BITTENSOR_HPP

#include <cstdint>
#include <concepts>
#include <boost/dynamic_bitset.hpp>

#include "DiscreteSpace/Tensor.hpp"
#include "DiscreteSpace/Shape.hpp"

namespace DiscreteSpace {

/** Tensor of boolean values

Implementation of Tensor with boost::dynamic_bitsets
*/
template <std::size_t N>
class BitTensor : public Tensor<boost::dynamic_bitset<>, N> {
public:
// LIFECYCLE
	/** Constructor from shape
	Extends Tensor's constructor from shape.
	@param shape The reference to the shape for the tensor
	*/
	BitTensor(const Shape<N>& shape);

	/** Copy constructor
	@param from The reference from which values are copied to this object
	*/
	BitTensor(const BitTensor<N>& from);

	/** Virtual destructor
	Compiler-generated
	*/
	//virtual ~BitTensor() {}
	
protected:
	using Tensor<boost::dynamic_bitset<>, N>::shape;
	using Tensor<boost::dynamic_bitset<>, N>::tensor;

// OPERATIONS
	/** Tensor initializer
	
	Initializes the tensor of the object

	Called by the constructor from shape
	*/
	void init_tensor();

//private:
};

// INLINE METHODS
template<std::size_t N>
BitTensor<N>::BitTensor(const Shape<N>& shape) : Tensor<boost::dynamic_bitset<>, N>(shape) {
	init_tensor();
}

template<std::size_t N>
BitTensor<N>::BitTensor(const BitTensor<N>& from) : Tensor<boost::dynamic_bitset<>, N>(from) {}

template<std::size_t N>
void BitTensor<N>::init_tensor() {
	std::size_t size = 1;
	for (std::size_t i = 0; i < shape->get_rank(); ++i) {
		size *= shape->get_length(i);
	}
	tensor = boost::dynamic_bitset<>(size, 0);
}

}

#endif
