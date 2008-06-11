
#include <iostream>
#include "bot/memory.h"
#include "testlib.h"

using namespace test;
using namespace bot;

void testMemory()
{
	bool success = true;
	printTestName("Memory class");

	printTestStart("Constructor(uint), size()");
	Memory m(10);
	printTestResult( m.size() == 10 );

	printTestStart("resize()");
	m.resize(12);
	printTestResult( m.size() == 12 );

	printTestStart("clear()");
	m.clear();
	for ( unsigned int i = 0; i < m.size(); i++ ) if ( m.readChar(i) != 0 ) success = false;
	printTestResult(success);

	printTestStart("writeChar(), readChar()");
	m.writeChar(0,'a');
	printTestResult( m.readChar(0) == 'a' );

	printTestStart("writeInt(), readInt()");
	m.writeInt(0,-100);
	printTestResult( m.readInt(0) == -100 );

	printTestStart("writeUInt(), readUInt()");
	m.writeUInt(0,250);
	printTestResult( m.readUInt(0) == 250 );

	printTestStart("writeFloat(), readFloat()");
	m.writeFloat(0,100.0);
	float f = m.readFloat(0);
	std::cout << f;
	printTestResult( f == 1.0 );

	printTestResult();
}

int main( int argc, char** argv )
{
	std::cout << "MARS test suite executing." << std::endl;

	testMemory();

	if (printGlobalTestResult() ) return 0;
	else return 255;
}
