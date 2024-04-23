#ifndef TOPOLOGY_TWODIMENSIONAL_HPP
#define TOPOLOGY_TWODIMENSIONAL_HPP

#include <cstdint>

namespace Topology {

/** Enumerated type for 2D positions

Follows numpad notation
*/
public enum TwoDimensionalGrid {
	1=BottomLeft,
	2=Bottom,
	3=BottomRight,
	4=Left,
	5=Center,
	6=Right,
	7=TopLeft,
	8=Top,
	9=TopRight
};

/** Topology of a traditional 2D hitori board

Methods for checking adjacencies
*/
template <std::size_t N>
class TwoDimensional : public DiscreteSpace::ShapeAggregate<N> {
public:
// LIFECYCLE
	/** Constructor from shape
	
	Extends ShapeAggregate's constructor from shape.
	@param shape The reference to the shape for the board
	*/
	TwoDimensional(const Shape<N>& shape);

	/** Copy constructor
	@param from The reference from which values are copied to this object
	*/
	TwoDimensional(const TwoDimensional<N>& from);

	/** Virtual destructor
	
	Pure virtual function to make class abstract
	*/
	virtual TwoDimensional() = 0;

protected:
	using ShapeAggregate<N>::shape;

// OPERATIONS
	template<std::integral T>
	T get_cell(const T index) const;
};

// INLINE METHODS
template<std::size_t N>
TwoDimensional<N>::TwoDimensional(const DiscreteSpace::Shape<N>& shape) : DiscreteSpace::ShapeAggregate<N>(shape) {}

template<std::size_t N>
TwoDimensional<N>::TwoDimensional(const TwoDimensional<N>& from) {
	this->shape = from.shape;
}

template<std::size_t N>
template<std::integral T>
T TwoDimensional<N>::get_cell(const T index) const {
	return 0;
}

}

#endif // TOPOLOGY_TWODIMENSIONAL_HPP
