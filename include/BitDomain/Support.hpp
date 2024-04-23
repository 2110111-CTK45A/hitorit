#ifndef BITDOMAIN_SUPPORT_HPP
#define BITDOMAIN_SUPPORT_HPP

#include <vector>
#include <boost/dynamic_bitset.hpp>
#include <cstdint>

namespace BitDomain {

/**
Axes of bitsets representing subdomains of a tensor domain
*/
template <typename S = std::size_t>
class Support {
private:
	void add_axis(S size);
	void del_axis();
	void del_axis(S axis);

protected:
	std::vector<boost::dynamic_bitset<>> domain = std::vector<boost::dynamic_bitset<>>();

public:
	// CONSTRUCTOR
	template <typename... Ns>
	explicit Support(const Ns... n) {
		S domainSize[sizeof...(n)] = {n...};
		for (S i = 0; i < sizeof...(n); ++i) {
			add_axis(domainSize[i]);
		}
	}

	explicit Support(std::vector<S> v) {
	}

	// DESTRUCTOR
	//virtual Support();

	// GETTER
	S get_rank() const;
	std::vector<S> get_shape() const;
	boost::dynamic_bitset<> get_axis(const S axis) const;
	S get_axis_size(const S axis) const;

	// PROJECTION
	template <typename T = uint64_t>
	constexpr T get_projection(const S axis, const T index) const {
		switch (axis) {
			case 0:
				return index % get_axis_size(0);
			case 1:
				return std::ceil((float)index / get_axis_size(0));
			default:
				return get_projection<T>(axis - 1, std::ceil((float)index / get_axis_size(axis - 1)));
		}
	}

	template <typename T = uint64_t>
	constexpr bool is_in_subtensor(const S axis, const S n, const T index) const {
		return get_projection(axis, index) == n;
	}

	// BUILDER
	//constexpr Support<S> operator::+();
	//template <typename... Ns>
	//constexpr Support<S> add_axis(const Ns... n) {
		//S domainSize[sizeof...(n)] = {n...};
		//for (S i = 0; i < sizeof...(n); ++i) {
			//domain.push_back(boost::dynamic_bitset<>(domainSize[i]));
		//}
	//}
};

}

#endif
