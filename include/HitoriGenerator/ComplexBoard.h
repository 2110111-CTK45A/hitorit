#ifndef ComplexBoard_H
#define ComplexBoard_H


#include "BinaryBoard.h"
#include "EnforceList.h"
#include "ForbiddenList.h"

namespace HitoriGenerator {
struct Cell {
public:
	uint32_t value = 0, state = 0;
};

class ComplexBoard : public NumBoard {
public:
	ComplexBoard();
	ComplexBoard(const uint32_t rows, const uint32_t columns, bool isEmpty = false);
	ComplexBoard(BinaryBoard solution);
	~ComplexBoard();
	
	uint32_t get_value(const uint32_t index) const;
	void build();
	void show();
	
private:
	std::unique_ptr<std::uniform_int_distribution<uint32_t>> distribution;
	std::unique_ptr<std::vector<struct Cell>> cell;
	std::unique_ptr<std::vector<std::unique_ptr<std::vector<uint32_t>>>> unmarkedList;
	std::unique_ptr<ForbiddenList> forbiddenList;
	std::unique_ptr<EnforceList> enforceList;
	
	void __init_solution();
	bool __renew();
	bool __fill();
	
	void __forbid(const uint32_t index, const uint32_t value);
	void __unenforce_row(const uint32_t index, const uint32_t value);
	void __unenforce_column(const uint32_t index, const uint32_t value);
	bool __assign_unmarked(const uint32_t index);
	void __assign_marked(const uint32_t index);
	bool __assign_enforced(const uint32_t index);
	bool __assign_last_enforced(const uint32_t index);
	
	void __swap_in_column(const uint32_t index1, const uint32_t index2);
	void __swap_in_row(const uint32_t index1, const uint32_t index2);
	bool __has_remaining_enforces() const;
	
	void __init_unmarked();
	void __update_unmarked(const uint32_t index);
	
	bool __is_unfinished() const;
	bool __has_same_in_column(const uint32_t index) const;
	bool __has_same_in_row(const uint32_t index) const;
};
}


#endif
