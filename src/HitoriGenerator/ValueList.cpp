#include "HitoriGenerator/ValueList.h"

using namespace HitoriGenerator;

void ValueList::add_to_column(const uint32_t index, const uint32_t value) {
	get_columnList(index)->insert(value);
}
void ValueList::add_to_row(const uint32_t index, const uint32_t value) {
	get_rowList(index)->insert(value);
}
void ValueList::add(const uint32_t index, const uint32_t value) {
	add_to_row(index, value);
	add_to_column(index, value);
}

void ValueList::remove_from_column(const uint32_t index, const uint32_t value) {
	get_columnList(index)->erase(value);
}
void ValueList::remove_from_row(const uint32_t index, const uint32_t value) {
	get_rowList(index)->erase(value);
}
void ValueList::remove(const uint32_t index, const uint32_t value) {
	remove_from_row(index, value);
	remove_from_column(index, value);
}

bool ValueList::is_in_row(const uint32_t index, const uint32_t value) const {
	std::shared_ptr<std::set<uint32_t>> target = get_rowList(index);
	return target->find(value) != target->end();
}
bool ValueList::is_in_column(const uint32_t index, const uint32_t value) const {
	std::shared_ptr<std::set<uint32_t>> target = get_columnList(index);
	return target->find(value) != target->end();
}

std::shared_ptr<std::set<uint32_t>> ValueList::get_columnList(const uint32_t index) const {
	return (*columnList)[get_column_of(index)];
}
std::shared_ptr<std::set<uint32_t>> ValueList::get_rowList(const uint32_t index) const {
	return (*rowList)[get_row_of(index)];
}
uint32_t ValueList::get_row_of(const uint32_t index) const {
	return (uint32_t)(index / columnList->size());
}
uint32_t ValueList::get_column_of(const uint32_t index) const {
	return index % columnList->size();
}
