#ifndef DOCTEST_CONFIG_IMPLEMENT
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

int main(int argc, char** argv) {
	doctest::Context context;

	context.setOption("order-by", "name");

	context.applyCommandLine(argc, argv);

	int res = context.run();

	if(context.shouldExit())
		return res;

	int clientStuffReturnCode = 0;
	
	//your program

	return res + clientStuffReturnCode;
}

#endif
