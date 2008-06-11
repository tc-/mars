
#include <iostream>

#include "testlib.h"

namespace test
{

int failures_global = 0;
int failures_test = 0;
int num_tests_global = 0;
int num_tests = 0;

void printTestName( std::string name )
{
	std::cout << std::endl << "*** Testing [ " << name.c_str() << " ]:" << std::endl;
	failures_test = 0;
	num_tests = 0;
}

void printTestStart( std::string name )
{
	std::cout << " - Testing " << name.c_str() << " ... ";
	num_tests++;
}

void printTestResult( bool success )
{
	if ( success ) {
		std::cout << "ok";
	} else {
		std::cout << "FAILED!!!";
		failures_test++;
	}
	std::cout << std::endl;
}

void printTestResult()
{
	if ( failures_test > 0 )
		std::cout << "Result [ " << failures_test << " / " << (num_tests - failures_test) << " ] failed." << std::endl;
	else
		std::cout << "Result [ all ok ]" << std::endl;
	failures_global += failures_test;
	num_tests_global += num_tests;
}


bool printGlobalTestResult()
{
	std::cout << std::endl << std::endl;
	std::cout << "#######################################" << std::endl;
	std::cout << "##  Test results                     ##" << std::endl;
	std::cout << "#######################################" << std::endl << std::endl;
	std::cout << "Failures: " << failures_global << std::endl;
	std::cout << "Successful: " << num_tests_global - failures_global << std::endl;
	std::cout << "Total: " << num_tests_global << std::endl;
	if ( failures_global > 0 ) {
		std::cout << std::endl << "!!! WARNING !!!" << std::endl;
		std::cout << failures_global << " test(s) failed!" << std::endl;
	}
	return failures_global == 0;
}

}
