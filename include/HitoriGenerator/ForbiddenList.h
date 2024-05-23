#ifndef ForbiddenList_H
#define ForbiddenList_H


#include "ValueList.h"

namespace HitoriGenerator {
class ForbiddenList : public ValueList {
public:
	ForbiddenList();
	ForbiddenList(const uint32_t rows, const uint32_t columns);
	
	std::unique_ptr<std::vector<uint32_t>> get_possibility(const uint32_t index) const;
	bool is_valid(const uint32_t index, const uint32_t value) const;
};
}


#endif