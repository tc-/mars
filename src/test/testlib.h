#ifndef TESTLIB_H
#define TESTLIB_H

#include <string>
#include <stdexcept>

namespace test
{

void printTestName( std::string name );
void printTestResult();

void printTestStart( std::string name );
void printTestResult( bool success );

bool printGlobalTestResult();

void printException( std::exception& e );

}

#endif // TESTLIB_H
