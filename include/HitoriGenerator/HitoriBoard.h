#ifndef HitoriBoard_H
#define HitoriBoard_H


#include "TestBoard.h"

namespace HitoriGenerator {
class HitoriBoard {
public:
	HitoriBoard();
	HitoriBoard(const uint32_t rows, const uint32_t columns);
	HitoriBoard(const uint32_t size);
	~HitoriBoard();
	
	uint32_t rows, columns;
	std::vector<uint32_t> matrix;
	std::set<uint32_t> solution;
	
	void show();
};
}


#endif
