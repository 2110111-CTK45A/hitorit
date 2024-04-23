#ifndef DISCRETESPACE_SHAPE_HPP
#define DISCRETESPACE_SHAPE_HPP

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <concepts> // std::integral

namespace DiscreteSpace {

/** Shape for tensors */
template <std::size_t N = 2>
class Shape {
public:
// LIFECYCLE
	/** Constructor from lengths
	@param n Variadic arguments of the lengths for each dimension
	*/
	template <std::integral... Ns>
	explicit Shape(const Ns... n) {
		axes = {static_cast<std::size_t>(n)...};
	}

// ACCESS
	// GETTER
	std::size_t get_rank() const;
	std::size_t get_length(const std::integral auto axis) const;
	std::size_t get_max_length() const;

	// ITERATOR
	auto cbegin() const;
	auto cend() const;

// OPERATIONS
	// PROJECTION
	std::integral auto get_projection(const std::size_t axis, const std::integral auto index) const {
		switch (axis) {
			case 0:
				return index % get_length(0);
			case 1:
				return (std::size_t)std::floor((float)index / get_length(0));
			default:
				return get_projection(axis - 1, (std::size_t)std::floor((float)index / get_length(axis - 1)));
		}
	}

	template<std::integral T>
	constexpr std::array<T, N> get_coordinates(const T index) const {
		std::array<T, N> result;
		for (std::size_t i = 0; i < N; ++i) {
			result[i] = get_projection(i, index);
		}
		return result;
	}

	template<std::unsigned_integral... Ns>
	std::size_t get_index(const Ns... n) const;

	
private:
	std::array<std::size_t, N> axes;
};

// INLINE METHODS
template<std::size_t N>
std::size_t Shape<N>::get_length(const std::integral auto axis) const {
	return axes[axis];
}

template<std::size_t N>
std::size_t Shape<N>::get_max_length() const {
	return *std::max_element(axes.begin(), axes.end());
}

template<std::size_t N>
template<std::unsigned_integral... Ns>
std::size_t Shape<N>::get_index(const Ns... n) const {
	if (sizeof...(n) != N) {
		return 0;
	}
	std::size_t index = 0;
	std::size_t multiplier = 1;
	std::array v = {n...};
	
	for (std::size_t i = 0; i < N; ++i) {
		index += v[i]*multiplier;
		multiplier *= get_length(i);
	}
	return index;
}

}

#endif
