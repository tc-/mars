
#include <iostream>
#include "bot/memory.h"
#include "testlib.h"

using namespace test;

extern void testMemory();

int main( int argc, char** argv )
{
	std::cout << "#######################################" << std::endl;
	std::cout << "## MARS kikkass test suite executing ##" << std::endl;
	std::cout << "#######################################" << std::endl;

	testMemory();

	if (printGlobalTestResult() ) return 0;
	else return 255;
}
