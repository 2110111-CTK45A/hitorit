#ifndef BinaryBoard_H
#define BinaryBoard_H


#include "NumBoard.h"

namespace HitoriGenerator {
class BinaryBoard : public NumBoard{
public:
	BinaryBoard();
	BinaryBoard(const uint32_t rows, const uint32_t columns, bool isEmpty = false);
	~BinaryBoard();
	
	uint32_t get_cell(const uint32_t index) const;
	void set_cell(const uint32_t index, const uint32_t value);
	bool check_adjacent(const uint32_t index) const;
	bool check_diagonal(const uint32_t index) const;
	void show();
	

private:
	std::unique_ptr<std::vector<uint32_t>> cell, state0;
	
	void __renew();
	void __toggle(const uint32_t index);
	void __toggle_marked(const uint32_t index);
	void __toggle_safe(const uint32_t index);
	void __toggle_adjacent(const uint32_t index);
	void __toggle_diagonal(const uint32_t index);
	bool __qcheck_diagonal(const uint32_t index);
	uint32_t __count_border(const uint32_t index, const uint32_t offset, const uint32_t origin) const;
	
	bool __is_solved() const;
};
}


#endif