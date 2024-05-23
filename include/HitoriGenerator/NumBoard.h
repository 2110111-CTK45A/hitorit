#ifndef NumBoard_H
#define NumBoard_H


#include "Common.h"

namespace HitoriGenerator {
class NumBoard {
public:
	uint32_t rows, columns;
	std::shared_ptr<std::set<uint32_t>> get_solution() const;
	
protected:
	std::shared_ptr<std::set<uint32_t>> solution;

	int32_t _get_position(const uint32_t index, const uint32_t offset) const;
	
	bool _is_top(const uint32_t index) const;
	bool _is_bottom(const uint32_t index) const;
	bool _is_left(const uint32_t index) const;
	bool _is_right(const uint32_t index) const;
	bool _is_border(const uint32_t index) const;
};
}


#endif