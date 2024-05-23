#include "HitoriGenerator/HitoriBoard.h"

using namespace HitoriGenerator;

HitoriBoard::HitoriBoard() {
	
}
HitoriBoard::HitoriBoard(const uint32_t rows, const uint32_t columns) {
	std::unique_ptr<TestBoard> tb = std::unique_ptr<TestBoard>(new TestBoard(rows, columns));
	this->rows = rows;
	this->columns = columns;
	matrix = tb->get_cell();
	solution = *(tb->get_solution());
}
//HitoriBoard::HitoriBoard(const uint32_t size) {
	//auto hitori = new Pipeline(new SolutionHandler()).add_handler(new ComplexHandler()).add_handler(new TestHandler());
	//hitori.execute(size).show();
//}
HitoriBoard::~HitoriBoard() {
	
}
void HitoriBoard::show() {
	uint32_t k = 0;
	for (std::vector<uint32_t>::iterator i = matrix.begin(); i != matrix.end(); ++i) {
		std::cout<<*i<<' ';
		if (++k == columns) {
			std::cout<<'\n';
			k = 0;
		}
	}
	std::cout<<'\n';
	for (std::set<uint32_t>::iterator i = solution.begin(); i != solution.end(); ++i) {
		std::cout<<*i<<' ';
	}
	std::cout<<'\n';
}
