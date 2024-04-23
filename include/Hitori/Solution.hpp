#ifndef HITORI_SOLUTION_HPP
#define HITORI_SOLUTION_HPP

#include <cstdint>
#include <iostream>
#include <string>
#include <boost/dynamic_bitset.hpp>

#include "DiscreteSpace/BitTensor.hpp"
#include "DiscreteSpace/Shape.hpp"

namespace Hitori {

/** Solution to a hitori puzzle

A BitTensor with solution generation methods
*/
template <std::size_t N>
class Solution : public DiscreteSpace::BitTensor<N> {
public:
// LIFECYCLE
	/** Constructor from shape
	Extends BitTensor's constructor from shape.
	@param shape The reference to the shape for the board
	*/
	Solution(const DiscreteSpace::Shape<N>& shape);

	/** Copy constructor
	@param from The reference from which values are copied to this object
	*/
	Solution(const Solution<N>& from);

// ACCESS

// OPERATIONS
	bool set_cell(const std::integral auto index, const bool value);
	bool check_adjacent(const uint8_t index) const;
	bool check_diagonal(const uint8_t index) const;
	std::string to_string();

protected:
	using DiscreteSpace::BitTensor<N>::shape;
	using DiscreteSpace::BitTensor<N>::tensor;
	
private:
	void renew();
	void toggle(const uint32_t index);
	void toggle_marked(const uint32_t index);
	void toggle_safe(const uint32_t index);
	void toggle_adjacent(const uint32_t index);
	void toggle_diagonal(const uint32_t index);
	bool qcheck_diagonal(const uint32_t index);
	uint32_t count_border(const uint32_t index, const uint32_t offset, const uint32_t origin) const;
	
	bool is_solved() const;
};

// INLINE METHODS
template<std::size_t N>
Hitori::Solution<N>::Solution(const DiscreteSpace::Shape<N>& shape) : DiscreteSpace::BitTensor<N>(shape) {}

template<std::size_t N>
Hitori::Solution<N>::Solution(const Hitori::Solution<N>& from) : DiscreteSpace::BitTensor<N>(from) {}

}

#endif // HITORI_SOLUTION_HPP
