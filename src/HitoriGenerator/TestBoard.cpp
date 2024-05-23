#include "HitoriGenerator/TestBoard.h"
#include "doctest.h"

using namespace HitoriGenerator;

// DEFINITION
TestBoard::TestBoard() {
	
}
TestBoard::TestBoard(const uint32_t rows, const uint32_t columns) {
	this->rows = rows;
	this->columns = columns;
	complexBoard = std::unique_ptr<ComplexBoard>(new ComplexBoard(rows, columns, true));
	bin = std::unique_ptr<BinaryBoard>(new BinaryBoard(rows, columns, true));
	__build();
}
TestBoard::TestBoard(ComplexBoard complexBoard) {

}
TestBoard::~TestBoard() {
	
}

std::vector<uint32_t> TestBoard::get_cell() {
	return *cell;
}
void TestBoard::show() {
	if (cell->size() == 0) {
		return;
	}
	for (uint32_t i = 0; i < rows; ++i) {
		for (uint32_t j = 0; j < columns; ++j) {
			std::cout<<(*cell)[i*columns+j]<<' ';
		}
		std::cout<<'\n';
	}
}

void TestBoard::__build() {
	while (!__renew()) {}
}
bool TestBoard::__renew() {
	complexBoard->build();
	cell = std::unique_ptr<std::vector<uint32_t>>(new std::vector<uint32_t>());
	for (uint32_t i = 0; i < rows*columns; ++i) {
		cell->push_back(complexBoard->get_value(i));
	}
	solution = complexBoard->get_solution();
	__init_candidates();
	return __is_valid();
}
bool TestBoard::__is_valid() {
	for (std::set<uint32_t>::iterator i = candidates->begin(); i != candidates->end(); ++i) {
		if (__has_same_in_row(*i) || __has_same_in_column(*i)) {
			if (__test(*i)) {
				return false;
			}
		}
	}
	return true;
}
void TestBoard::__init_candidates() {
	std::unique_ptr<std::set<uint32_t>> coords = std::unique_ptr<std::set<uint32_t>>(new std::set<uint32_t>());
	for (uint32_t i = 0; i < rows*columns; ++i) {
		coords->insert(i);
	}
	std::unique_ptr<std::vector<uint32_t>> difference = std::unique_ptr<std::vector<uint32_t>>(new std::vector<uint32_t>(rows*columns)), sol = std::unique_ptr<std::vector<uint32_t>>(new std::vector<uint32_t>(solution->begin(), solution->end()));
	
	std::vector<uint32_t>::iterator oit = std::set_difference(coords->begin(), coords->end(), solution->begin(), solution->end(), difference->begin());
	candidates = std::unique_ptr<std::set<uint32_t>>(new std::set<uint32_t>(difference->begin(), oit));
}
bool TestBoard::__has_same_in_column(const uint32_t index) {
	uint32_t ct = 0;
	for (uint32_t i = index % columns; i < cell->size(); i += columns) {
		if ((*cell)[i] == (*cell)[index]) {
			if (++ct == 2) {
				return true;
			}
		}
	}
	return false;
}
bool TestBoard::__has_same_in_row(const uint32_t index) {
	uint32_t ct = 0, i = (uint32_t)(index/columns)*columns;
	for (uint32_t j = 0; j < columns; ++j) {
		if ((*cell)[i+j] == (*cell)[index]) {
			if (++ct == 2) {
				return true;
			}
		}
	}
	return false;
}
bool TestBoard::__mark_in_column(const uint32_t index) {
	for (uint32_t i = index%columns; i < rows*columns; i += columns) {
		if ((*cell)[i] == (*cell)[index]) {
			if (i != index) {
				switch (bin->get_cell(i)) {
					case 0: {
						if (!__mark(i)) {
							return false;
						}
						break;
					}
					case 2: {
						return false;
					}
					default: {
						break;
					}
				}
			}
		}
	}
	return true;
}
bool TestBoard::__mark_in_row(const uint32_t index) {
	uint32_t i = (uint32_t)(index/columns)*columns;
	for (uint32_t j = 0; j < columns; ++j) {
		if ((*cell)[i+j] == (*cell)[index]) {
			if (i+j != index) {
				switch (bin->get_cell(i+j)) {
					case 0: {
						if (!__mark(i+j)) {
							return false;
						}
						break;
					}
					case 2: {
						return false;
					}
					default: {
						break;
					}
				}
			}
		}
	}
	return true;
}
bool TestBoard::__mark(const uint32_t index) {
	if (!bin->check_adjacent(index)) {
		return false;
	}
	if (!bin->check_diagonal(index)) {
		return false;
	}
	bin->set_cell(index, 1);
	
	for (uint32_t i : {2, 4, 6, 8}) {
		int32_t target = _get_position(index, i);
		if (target >= 0) {
			if (!__protect(target)) {
				return false;
			}
		}
	}
	return true;
}
bool TestBoard::__protect(const uint32_t index) {
	switch (bin->get_cell(index)) {
		case 0: {
			bin->set_cell(index, 2);
			if (!__mark_in_row(index)) {
				return false;
			}
			if (!__mark_in_column(index)) {
				return false;
			}
			break;
		}
		case 1: {
			return false;
		}
		default: {
			break;
		}
	}
	return true;
}
bool TestBoard::__sweep() {
	for (uint32_t i = 0; i < rows*columns; ++i) {
		if (bin->get_cell(i) == 0) {
			if (!bin->check_diagonal(i)) {
				if (!__protect(i)) {
					return false;
				}
				hasChanged = true;
			}
		}
	}
	return true;
}
bool TestBoard::__test(const uint32_t index) {
	bin.reset(new BinaryBoard(rows, columns, true));
	if (__mark(index)) {
		while (true) {
			hasChanged = false;
			if (!__sweep()) {
				return false;
			}
			if (hasChanged == false) {
				return true;
			}
		}
	}
	return false;
}

// UNIT TEST
TEST_CASE("TestBoard fuzz") {
	for (auto i = 2; i < 10; ++i) {
		for (auto j = 0; j < 10; ++j) {
			TestBoard a(i,i);
			//a.show();
			//std::cout<<'\n';
		}
	}
}
