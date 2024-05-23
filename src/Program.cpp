#ifndef DOCTEST_CONFIG_IMPLEMENT
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include <string>
#include <chrono>
#include "HitoriGenerator/HitoriBoard.h"

using namespace HitoriGenerator;

int main(int argc, char** argv) {
	HitoriBoard a;
	auto start = std::chrono::high_resolution_clock::now();
	switch(argc) {
		case 2:
			a = HitoriBoard(std::stoi(argv[1]), std::stoi(argv[1]));
			break;
		case 3:
			a = HitoriBoard(std::stoi(argv[1]), std::stoi(argv[2]));
			break;
		default:
			a = HitoriBoard(9,9);
			break;
	}
	auto stop = std::chrono::high_resolution_clock::now();
	a.show();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout<<"Execution time "<<duration.count()<<"ms\n";
	return 0;
}

#endif
