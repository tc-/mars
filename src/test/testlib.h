#ifndef TESTLIB_H
#define TESTLIB_H

#include <string>

namespace test
{

void printTestName( std::string name );
void printTestResult();

void printTestStart( std::string name );
void printTestResult( bool success );

bool printGlobalTestResult();

}

#endif // TESTLIB_H
