#ifndef EnforceList_H
#define EnforceList_H


#include "ValueList.h"

namespace HitoriGenerator {
class EnforceList : public ValueList {
public:
	EnforceList();
	EnforceList(const uint32_t rows, const uint32_t columns);
};
}


#endif