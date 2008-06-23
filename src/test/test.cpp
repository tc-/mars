
#include <iostream>
#include "testlib.h"

using namespace test;

extern void testMemory();
extern void testVM();

int main( int argc, char** argv )
{
	std::cout << "#######################################" << std::endl;
	std::cout << "## MARS kikkass test suite executing ##" << std::endl;
	std::cout << "#######################################" << std::endl;

	std::cout << std::getenv("PWD") << std::endl;

	testMemory();
	testVM();

	if (printGlobalTestResult() ) return 0;
	else return 255;
}
