#include "HitoriGenerator/ComplexBoard.h"
#include "doctest.h"

using namespace HitoriGenerator;

// DEFINITION
ComplexBoard::ComplexBoard() {
	
}
ComplexBoard::ComplexBoard(const uint32_t rows, const uint32_t columns, bool isEmpty) {
	this->rows = rows;
	this->columns = columns;
	distribution = std::unique_ptr<std::uniform_int_distribution<uint32_t>>(new std::uniform_int_distribution<uint32_t>(1, (rows < columns) ? columns : rows));
	if (!isEmpty) {
		build();
	}
}
ComplexBoard::ComplexBoard(BinaryBoard solution) {
	return;
}
ComplexBoard::~ComplexBoard() {
	
}

uint32_t ComplexBoard::get_value(const uint32_t index) const {
	return (*cell)[index].value;
}
void ComplexBoard::build() {
	while (!__renew()) {}
}
void ComplexBoard::show() {
	if (cell->size() == 0) {
		return;
	}
	for (uint32_t i = 0; i < rows; ++i) {
		for (uint32_t j = 0; j < rows; ++j) {
			std::cout<<(*cell)[i*columns+j].value<<(*cell)[i*columns+j].state<<' ';
		}
		std::cout<<'\n';
	}
}

bool ComplexBoard::__renew() {
	cell = std::unique_ptr<std::vector<struct Cell>>(new std::vector<struct Cell>);
	for (uint32_t i = 0; i < rows*columns; ++i) {
		cell->push_back(Cell{0,0});
	}
	forbiddenList = std::unique_ptr<ForbiddenList>(new ForbiddenList(rows, columns));
	enforceList = std::unique_ptr<EnforceList>(new EnforceList(rows, columns));
	__init_solution();
	__init_unmarked();
	for (uint32_t i : *solution){
		(*cell)[i].state = 1;
	}
	return __fill();
}
bool ComplexBoard::__fill() {
	for (uint32_t i = 0; i < rows; ++i) {
		for (uint32_t j = 0; j < columns; ++j) {
			uint32_t index = i*columns+j;
			if ((*cell)[index].state == 1) {
				__assign_marked(index);
			} else {
				size_t remainingEnforces = enforceList->get_columnList(j)->size();
				if (remainingEnforces >= (*((*unmarkedList)[1]))[j]) {
					if (!__assign_enforced(index)) {
						return false;
					}
				} else {
					if (i == rows - 1) {
						remainingEnforces = enforceList->get_rowList(i)->size();
						if (remainingEnforces >= (*((*unmarkedList)[1]))[j]) {
							if (!__assign_last_enforced(index)) {
								return false;
							}
						}
					}
					if (!__assign_unmarked(index)) {
						return false;
					}
				}
			}
		}
	}
	if (__has_remaining_enforces()) {
		return false;
	}
	return true;
}

void ComplexBoard::__forbid(const uint32_t index, const uint32_t value) {
	forbiddenList->remove(index, value);
	__unenforce_row(index, value);
	__unenforce_column(index, value);
}
void ComplexBoard::__unenforce_row(const uint32_t index, const uint32_t value) {
	uint32_t row = enforceList->get_row_of(index);
	std::shared_ptr<std::set<uint32_t>> target = enforceList->get_rowList(row);
	if (target->find(value) != target->end()) {
		for (uint32_t i = 0; i < columns; ++i) {
			uint32_t dest = row*columns+i;
			if ((*cell)[dest].value == value) {
				if ((*cell)[dest].state == 1) {
					enforceList->remove_from_column(dest, value);
				}
			}
		}
		enforceList->remove_from_row(index, value);
	}
}
void ComplexBoard::__unenforce_column(const uint32_t index, const uint32_t value) {
	uint32_t column = enforceList->get_column_of(index);
	std::shared_ptr<std::set<uint32_t>> target = enforceList->get_columnList(column);
	if (target->find(value) != target->end()) {
		for (uint32_t i = 0; i < rows; ++i) {
			uint32_t dest = columns*i+column;
			if ((*cell)[dest].value == value) {
				if ((*cell)[dest].state == 1) {
					enforceList->remove_from_row(dest, value);
				}
			}
		}
		enforceList->remove_from_column(index, value);
	}
}
bool ComplexBoard::__assign_unmarked(const uint32_t index) {
	std::unique_ptr<std::vector<uint32_t>> possibility = forbiddenList->get_possibility(index);
	if (possibility->size() == 0) {
		return false;
	}
	std::shuffle(possibility->begin(), possibility->end(), mt);
	(*cell)[index].value = possibility->front();
	__forbid(index, possibility->front());
	__update_unmarked(index);
	return true;
}
void ComplexBoard::__assign_marked(const uint32_t index) {
	uint32_t value = (*distribution)(mt);
	(*cell)[index].value = value;
	if (!forbiddenList->is_in_row(index, value)) {
		return;
	}
	if (!forbiddenList->is_in_column(index, value)) {
		return;
	}
	enforceList->add(index, value);
}
bool ComplexBoard::__assign_enforced(const uint32_t index) {
	uint32_t i = forbiddenList->get_column_of(index);
	std::unique_ptr<std::vector<uint32_t>> pool = forbiddenList->get_possibility(index);
	std::unique_ptr<std::vector<uint32_t>> req = std::unique_ptr<std::vector<uint32_t>>(new std::vector<uint32_t>(enforceList->get_columnList(i)->begin(), enforceList->get_columnList(i)->end())), intersection = std::unique_ptr<std::vector<uint32_t>>(new std::vector<uint32_t>((pool->size() > req->size()) ? pool->size() : req->size()));
	std::vector<uint32_t>::iterator oit = std::set_intersection(pool->begin(), pool->end(), req->begin(), req->end(), intersection->begin());
	std::unique_ptr<std::vector<uint32_t>> possibilities = std::unique_ptr<std::vector<uint32_t>>(new std::vector<uint32_t>(intersection->begin(), oit));
	
	if (possibilities->size() == 0) {
		std::shuffle(req->begin(), req->end(), mt);
		(*cell)[index].value = req->front();
		std::unique_ptr<std::vector<uint32_t>> options = std::unique_ptr<std::vector<uint32_t>>(new std::vector<uint32_t>());
		for ( ; i < index; i += columns) {
			if ((*cell)[i].state == 0) {
				if (!__has_same_in_row(i)) {
					if (forbiddenList->is_valid(i, (*cell)[index].value)) {
						options->push_back(i);
					}
				}
			}
		}
		if (options->size() == 0) {
			return false;
		} else {
			std::shuffle(options->begin(), options->end(), mt);
			__swap_in_column(options->front(), index);
		}
	} else {
		std::shuffle(possibilities->begin(), possibilities->end(), mt);
		(*cell)[index].value = possibilities->front();
		__forbid(index, (*cell)[index].value);
		__update_unmarked(index);
	}
	return true;
}
bool ComplexBoard::__assign_last_enforced(const uint32_t index) {
	uint32_t i = forbiddenList->get_row_of(index);
	std::unique_ptr<std::vector<uint32_t>> pool = forbiddenList->get_possibility(index);
	std::unique_ptr<std::vector<uint32_t>> req = std::unique_ptr<std::vector<uint32_t>>(new std::vector<uint32_t>(enforceList->get_rowList(i)->begin(), enforceList->get_rowList(i)->end())), intersection = std::unique_ptr<std::vector<uint32_t>>(new std::vector<uint32_t>((pool->size() > req->size()) ? pool->size() : req->size()));
	std::vector<uint32_t>::iterator oit = std::set_intersection(pool->begin(), pool->end(), req->begin(), req->end(), intersection->begin());
	std::unique_ptr<std::vector<uint32_t>> possibilities = std::unique_ptr<std::vector<uint32_t>>(new std::vector<uint32_t>(intersection->begin(), oit));
	
	if (possibilities->size() == 0) {
		std::shuffle(req->begin(), req->end(), mt);
		(*cell)[index].value = req->front();
		std::unique_ptr<std::vector<uint32_t>> options = std::unique_ptr<std::vector<uint32_t>>(new std::vector<uint32_t>());
		for (uint32_t j = i*columns; j < rows*columns; ++j) {
			if ((*cell)[j].state == 0) {
				if (!__has_same_in_column(j)) {
					if (forbiddenList->is_valid(j, (*cell)[index].value)) {
						options->push_back(j);
					}
				}
			}
		}
		if (options->size() == 0) {
			return false;
		} else {
			std::shuffle(options->begin(), options->end(), mt);
			__swap_in_row(options->front(), index);
		}
	} else {
		std::shuffle(possibilities->begin(), possibilities->end(), mt);
		(*cell)[index].value = possibilities->front();
		__forbid(index, (*cell)[index].value);
		__update_unmarked(index);
	}
	return true;
}

void ComplexBoard::__swap_in_column(const uint32_t index1, const uint32_t index2) {
	uint32_t temp = (*cell)[index1].value;
	forbiddenList->add_to_row(index1, temp);
	(*cell)[index1].value = (*cell)[index2].value;
	forbiddenList->remove_from_row(index1, (*cell)[index1].value);
	forbiddenList->add_to_row(index2, (*cell)[index2].value);
	(*cell)[index2].value = temp;
	forbiddenList->remove_from_row(index2, temp);
}
void ComplexBoard::__swap_in_row(const uint32_t index1, const uint32_t index2) {
	uint32_t temp = (*cell)[index1].value;
	forbiddenList->add_to_column(index1, temp);
	(*cell)[index1].value = (*cell)[index2].value;
	forbiddenList->remove_from_column(index1, (*cell)[index1].value);
	forbiddenList->add_to_column(index2, (*cell)[index2].value);
	(*cell)[index2].value = temp;
	forbiddenList->remove_from_column(index2, temp);
}
bool ComplexBoard::__has_remaining_enforces() const {
	for (uint32_t i = 0; i < columns; ++i) {
		if (enforceList->get_columnList(i)->size() != 0) {
			return true;
		}
	}
	for (uint32_t i = 0; i < rows; ++i) {
		if (enforceList->get_rowList(i)->size() != 0) {
			return true;
		}
	}
	return false;
}

void ComplexBoard::__init_solution() {
	this->solution = BinaryBoard(rows, columns).get_solution();
}
void ComplexBoard::__init_unmarked() {
	unmarkedList = std::unique_ptr<std::vector<std::unique_ptr<std::vector<uint32_t>>>>(new std::vector<std::unique_ptr<std::vector<uint32_t>>>());
	unmarkedList->push_back(std::unique_ptr<std::vector<uint32_t>>(new std::vector<uint32_t>));
	unmarkedList->push_back(std::unique_ptr<std::vector<uint32_t>>(new std::vector<uint32_t>));
	for (uint32_t i = 0; i < rows; ++i) {
		(*unmarkedList)[0]->push_back(columns);
	}
	for (uint32_t i = 0; i < columns; ++i) {
		(*unmarkedList)[1]->push_back(rows);
	}
	for (uint32_t i : *solution) {
		__update_unmarked(i);
	}
}
void ComplexBoard::__update_unmarked(const uint32_t index) {
	(*((*unmarkedList)[0]))[forbiddenList->get_row_of(index)]--;
	(*((*unmarkedList)[1]))[forbiddenList->get_column_of(index)]--;
}

bool ComplexBoard::__is_unfinished() const {
	for (struct Cell i : *cell) {
		if (i.value*i.state == 0) {
			return true;
		}
	}
	return false;
}
bool ComplexBoard::__has_same_in_column(const uint32_t index) const {
	uint32_t ct = 0;
	for (uint32_t i = index%columns; i < cell->size(); i += columns) {
		if ((*cell)[i].value == (*cell)[index].value) {
			if (++ct == 2) {
				return true;
			}
		}
	}
	return false;
}
bool ComplexBoard::__has_same_in_row(const uint32_t index) const {
	uint32_t ct = 0, i = (uint32_t)(index/columns)*columns;
	for (uint32_t j = 0; j < columns; ++j) {
		if ((*cell)[i+j].value == (*cell)[index].value) {
			if (++ct == 2) {
				return true;
			}
		}
	}
	return false;
}

// UNIT TEST
TEST_CASE("ComplexBoard fuzz") {
	for (auto i = 2; i < 10; ++i) {
		for (auto j = 0; j < 10; ++j) {
			ComplexBoard a(i,i);
			//a.show();
			//std::cout<<'\n';
		}
	}
}
