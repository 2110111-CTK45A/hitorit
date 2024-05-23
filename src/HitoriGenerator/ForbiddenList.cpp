#include "HitoriGenerator/ForbiddenList.h"
#include "doctest.h"

using namespace HitoriGenerator;

ForbiddenList::ForbiddenList() {
	
}
ForbiddenList::ForbiddenList(const uint32_t rows, const uint32_t columns) {
	rowList = std::unique_ptr<std::vector<std::shared_ptr<std::set<uint32_t>>>>(new std::vector<std::shared_ptr<std::set<uint32_t>>>());
	columnList = std::unique_ptr<std::vector<std::shared_ptr<std::set<uint32_t>>>>(new std::vector<std::shared_ptr<std::set<uint32_t>>>());
	uint32_t maxValue = (rows > columns) ? rows : columns;
	for (uint32_t i = 0; i < rows; ++i) {
		std::shared_ptr<std::set<uint32_t>> temp = std::shared_ptr<std::set<uint32_t>>(new std::set<uint32_t>);
		for (uint32_t j = 1; j <= maxValue; ++j) {
			temp->insert(j);
		}
		rowList->push_back(temp);
	}
	for (uint32_t i = 0; i < columns; ++i) {
		std::shared_ptr<std::set<uint32_t>> temp = std::shared_ptr<std::set<uint32_t>>(new std::set<uint32_t>);
		for (uint32_t j = 1; j <= maxValue; ++j) {
			temp->insert(j);
		}
		columnList->push_back(temp);
	}
}

std::unique_ptr<std::vector<uint32_t>> ForbiddenList::get_possibility(const uint32_t index) const {
	std::vector<uint32_t> returnSet = std::vector<uint32_t>((get_rowList(index)->size() > get_columnList(index)->size()) ? get_rowList(index)->size() : get_columnList(index)->size());
	std::vector<uint32_t>::iterator oit;
	oit = std::set_intersection(get_rowList(index)->begin(), get_rowList(index)->end(), get_columnList(index)->begin(), get_columnList(index)->end(), returnSet.begin());
	return std::unique_ptr<std::vector<uint32_t>>(new std::vector<uint32_t>(returnSet.begin(), oit));
}
bool ForbiddenList::is_valid(const uint32_t index, const uint32_t value) const {
	std::unique_ptr<std::vector<uint32_t>> intersection = get_possibility(index);
	std::set<uint32_t> possibility(intersection->begin(), intersection->end());
	return possibility.find(value) != possibility.end();
}
