#ifndef ValueList_H
#define ValueList_H


#include "Common.h"

namespace HitoriGenerator {
class ValueList {
public:	
	void add_to_row(const uint32_t index, const uint32_t value);
	void add_to_column(const uint32_t index, const uint32_t value);
	void add(const uint32_t index, const uint32_t value);
	
	void remove_from_row(const uint32_t index, const uint32_t value);
	void remove_from_column(const uint32_t index, const uint32_t value);
	void remove(const uint32_t index, const uint32_t value);
	
	bool is_in_row(const uint32_t index, const uint32_t value) const;
	bool is_in_column(const uint32_t index, const uint32_t value) const;
	
	std::shared_ptr<std::set<uint32_t>> get_rowList(const uint32_t index) const;
	std::shared_ptr<std::set<uint32_t>> get_columnList(const uint32_t index) const;
	uint32_t get_row_of(const uint32_t index) const;
	uint32_t get_column_of(const uint32_t index) const;
	
protected:
	std::unique_ptr<std::vector<std::shared_ptr<std::set<uint32_t>>>> rowList, columnList;
};
}


#endif