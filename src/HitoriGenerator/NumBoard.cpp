#include "HitoriGenerator/NumBoard.h"
#include "doctest.h"

using namespace HitoriGenerator;

std::shared_ptr<std::set<uint32_t>> NumBoard::get_solution() const {
	return solution;
}

int32_t NumBoard::_get_position(const uint32_t index, const uint32_t offset) const {
	switch(offset) {
		case 1: {
			if (_is_top(index) || _is_left(index)) {
				break;
			} else {
				return index - columns - 1;
			}
		}
		case 2: {
			if (_is_top(index)) {
				break;
			} else {
				return index - columns;
			}
		}
		case 3: {
			if (_is_top(index) || _is_right(index)) {
				break;
			} else {
				return index - columns + 1;
			}
		}
		case 4: {
			if (_is_left(index)) {
				break;
			} else {
				return index - 1;
			}
		}
		case 6: {
			if (_is_right(index)) {
				break;
			} else {
				return index + 1;
			}
		}
		case 7: {
			if (_is_bottom(index) || _is_left(index)) {
				break;
			} else {
				return index + columns - 1;
			}
		}
		case 8: {
			if (_is_bottom(index)) {
				break;
			} else {
				return index + columns;
			}
		}
		case 9: {
			if (_is_bottom(index) || _is_right(index)) {
				break;
			} else {
				return index + columns + 1;
			}
		}
	}
	return -1;
}

bool NumBoard::_is_top(const uint32_t index) const {
	return index < columns;
}
bool NumBoard::_is_bottom(const uint32_t index) const {
	return index >= columns * (rows - 1);
}
bool NumBoard::_is_left(const uint32_t index) const {
	return index % columns == 0;
}
bool NumBoard::_is_right(const uint32_t index) const {
	return _is_left(index + 1);
}
bool NumBoard::_is_border(const uint32_t index) const {
	return _is_top(index) || _is_bottom(index) || _is_left(index) || _is_right(index);
}
