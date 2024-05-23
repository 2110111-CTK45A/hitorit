#include "HitoriGenerator/BinaryBoard.h"
#include "doctest.h"

using namespace HitoriGenerator;

// DEFINITION
BinaryBoard::BinaryBoard() {
	
}
BinaryBoard::BinaryBoard(const uint32_t rows, const uint32_t columns, bool isEmpty) {
	this->rows = rows;
	this->columns = columns;
	
	cell = std::unique_ptr<std::vector<uint32_t>>(new std::vector<uint32_t>(rows*columns, 0));
	state0 = std::unique_ptr<std::vector<uint32_t>>(new std::vector<uint32_t>());
	solution = std::unique_ptr<std::set<uint32_t>>(new std::set<uint32_t>());
	
	if (!isEmpty) {
		__renew();
	}
}
BinaryBoard::~BinaryBoard() {
	
}

uint32_t BinaryBoard::get_cell(const uint32_t index) const {
	return (*cell)[index];
}
void BinaryBoard::set_cell(const uint32_t index, const uint32_t value) {
	(*cell)[index] = value%3;
}
bool BinaryBoard::check_adjacent(const uint32_t index) const {
	int32_t target;
	for (uint32_t i : {2, 4, 6, 8}) {
		target = _get_position(index, i);
		if (target >= 0) {
			if ((*cell)[target] == 1) {
				return false;
			}
		}
	}
	return true;
}
bool BinaryBoard::check_diagonal(const uint32_t index) const {
	uint32_t ct = (_is_border(index)) ? 1 : 0;
	int32_t target;
	for (uint32_t i : {1, 3, 7, 9}) {
		target = _get_position(index, i);
		if (target >= 0) {
			if (get_cell(target) == 1) {
				ct += __count_border(target, i, index);
				if (ct > 1) {
					return false;
				}
			}
		}
	}
	return true;
}
void BinaryBoard::show() {
	if (cell->size() == 0) {
		return;
	}
	for (uint32_t i = 0; i < rows; ++i) {
		for (uint32_t j = 0; j < rows; ++j) {
			switch((*cell)[i*columns+j]) {
				case 1: {
					std::cout<<"1";
					break;
				}
				case 2: {
					std::cout<<"2";
					break;
				}
				default: {
					std::cout<<"0";
					break;
				}
			}
		}
		std::cout<<'\n';
	}
}

void BinaryBoard::__renew() {
	for (uint32_t i = 0; i < cell->size(); ++i) {
		state0->push_back(i);
	}
	
	std::shuffle(state0->begin(), state0->end(), mt);
	
	for (std::vector<uint32_t>::iterator i = state0->begin(); !state0->empty(); i = state0->begin()) {
		if ((*cell)[*i] == 0) {
			__toggle(*i);
		}
	}
}
void BinaryBoard::__toggle(const uint32_t index) {
	if (__qcheck_diagonal(index)) {
		__toggle_marked(index);
		__toggle_adjacent(index);
		__toggle_diagonal(index);
	}
}
void BinaryBoard::__toggle_marked(const uint32_t index) {
	(*cell)[index] = 1;
	solution->insert(index);
	state0->erase(std::remove(state0->begin(), state0->end(), index), state0->end());
}
void BinaryBoard::__toggle_safe(const uint32_t index) {
	(*cell)[index] = 2;
	state0->erase(std::remove(state0->begin(), state0->end(), index), state0->end());
}
void BinaryBoard::__toggle_adjacent(const uint32_t index) {
	int32_t target;
	for (uint32_t i = 2; i < 10; i+=2) {
		target = _get_position(index, i);
		if (target >= 0) {
			if ((*cell)[target] == 0) {
				__toggle_safe(target);
			}
		}
	}
}
void BinaryBoard::__toggle_diagonal(const uint32_t index) {
	int32_t target;
	for (uint32_t i : {1, 3, 7, 9}) {
		target = _get_position(index, i);
		if (target >= 0) {
			if ((*cell)[target] == 0) {
				__qcheck_diagonal(target);
			}
		}
	}
}

bool BinaryBoard::__qcheck_diagonal(const uint32_t index) {
	uint32_t ct = (_is_border(index)) ? 1 : 0;
	int32_t target;
	for (uint32_t i : {1, 3, 7, 9}) {
		target = _get_position(index, i);
		if (target >= 0) {
			if ((*cell)[target] == 1) {
				ct += __count_border(target, i, index);
				if (ct > 1) {
					__toggle_safe(index);
					return false;
				}
			}
		}
	}
	return true;
}
uint32_t BinaryBoard::__count_border(const uint32_t index, const uint32_t offset, const uint32_t origin) const{
	uint32_t ct = (_is_border(index)) ? 1 : 0;
	int32_t target;
	std::set<uint32_t> dest({1, 3, 7, 9});
	dest.erase(10 - offset);
	for (uint32_t i : dest) {
		target = _get_position(index, i);
		if (target >= 0) {
			if (target == origin) {
				return 2;
			}
			if ((*cell)[target] == 1) {
				ct += __count_border(target, i, origin);
				if (ct > 1) {
					break;
				}
			}
		}
	}
	return ct;
}

bool BinaryBoard::__is_solved() const {
	for (std::vector<uint32_t>::iterator i = cell->begin(); i != cell->end(); ++i) {
		if (*i == 0) {
			return false;
		}
	}
	return true;
}


// UNIT TEST
TEST_CASE("BinaryBoard adjacency operations") {
	BinaryBoard a(4, 4, true);
	CHECK(a.check_adjacent(0));
	CHECK(a.check_adjacent(1));
	CHECK(a.check_adjacent(5));
	a.set_cell(0,1);
	CHECK(a.check_adjacent(0));
	CHECK(!a.check_adjacent(1));
	CHECK(a.check_adjacent(5));
	a.set_cell(0,2);
	a.set_cell(1,1);
	CHECK(!a.check_adjacent(0));
	CHECK(a.check_adjacent(1));
	CHECK(!a.check_adjacent(5));
	a.set_cell(1,2);
	a.set_cell(5,1);
	CHECK(a.check_adjacent(0));
	CHECK(!a.check_adjacent(1));
	CHECK(a.check_adjacent(5));
}

TEST_CASE("BinaryBoard diagonal operations") {
	BinaryBoard a(5, 5, true);
	CHECK(a.check_diagonal(0));
	CHECK(a.check_diagonal(1));
	CHECK(a.check_diagonal(11));
	// border border subcase
	a.set_cell(5,1);
	CHECK(a.check_diagonal(0));
	CHECK(!a.check_diagonal(1));
	CHECK(a.check_diagonal(11));
	a.set_cell(15,1);
	CHECK(!a.check_diagonal(11));
	a.set_cell(5,2);
	CHECK(a.check_diagonal(11));
	// 2 border subcase
	a.set_cell(7,1);
	a.set_cell(9,1);
	a.set_cell(13,1);
	CHECK(!a.check_diagonal(11));
	a.set_cell(15,2);
	CHECK(a.check_diagonal(11));
	// loop subcase
	a.set_cell(9,2);
	CHECK(a.check_diagonal(11));
	a.set_cell(17,1);
	CHECK(!a.check_diagonal(11));
}

TEST_CASE("BinaryBoard fuzz") {
	for (auto i = 2; i < 10; ++i) {
		for (auto j = 0; j < 10; ++j) {
			BinaryBoard a(i,i);
			//a.show();
			//std::cout<<'\n';
		}
	}
}
