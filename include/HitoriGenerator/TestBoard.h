#ifndef TestBoard_H
#define TestBoard_H


#include "ComplexBoard.h"

namespace HitoriGenerator {
class TestBoard : public NumBoard {
public:
	TestBoard();
	TestBoard(const uint32_t rows, const uint32_t columns);
	TestBoard(ComplexBoard complexBoard);
	~TestBoard();
	
	std::vector<uint32_t> get_cell();
	void show();
	
private:
	std::unique_ptr<ComplexBoard> complexBoard;
	std::unique_ptr<std::vector<uint32_t>> cell;
	std::unique_ptr<std::set<uint32_t>>  candidates;
	std::unique_ptr<BinaryBoard> bin;
	bool hasChanged;
	
	void __build();
	bool __renew();
	bool __is_valid();
	void __init_candidates();
	bool __has_same_in_column(const uint32_t index);
	bool __has_same_in_row(const uint32_t index);
	bool __mark(const uint32_t index);
	bool __mark_in_column(const uint32_t index);
	bool __mark_in_row(const uint32_t index);
	bool __protect(const uint32_t index);
	bool __sweep();
	bool __test(const uint32_t index);
};
}


#endif
