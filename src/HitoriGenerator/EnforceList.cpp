#include "HitoriGenerator/EnforceList.h"

using namespace HitoriGenerator;

EnforceList::EnforceList() {
	
}
EnforceList::EnforceList(const uint32_t rows, const uint32_t columns) {
	rowList = std::unique_ptr<std::vector<std::shared_ptr<std::set<uint32_t>>>>(new std::vector<std::shared_ptr<std::set<uint32_t>>>());
	columnList = std::unique_ptr<std::vector<std::shared_ptr<std::set<uint32_t>>>>(new std::vector<std::shared_ptr<std::set<uint32_t>>>());
	for (uint32_t i = 0; i < rows; ++i) {
		rowList->push_back(std::shared_ptr<std::set<uint32_t>>(new std::set<uint32_t>()));
	}
	for (uint32_t i = 0; i < columns; ++i) {
		columnList->push_back(std::shared_ptr<std::set<uint32_t>>(new std::set<uint32_t>()));
	}
}
