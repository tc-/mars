
#include <iostream>
#include <sstream>

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
	for ( unsigned int i = 0; i < m.size(); i++ ) if ( m.readByte(i) != 0 ) success = false;
	printTestResult(success);

	printTestStart("writeChar(), readChar()");
	m.writeByte(0,'a');
	printTestResult( m.readByte(0) == 'a' );

	printTestStart("writeInt(), readInt()");
	m.writeInt(0,-1000);
	printTestResult( m.readInt(0) == -1000 );

	printTestStart("writeUInt(), readUInt()");
	m.writeUInt(0,6553);
	printTestResult( m.readUInt(0) == 6553 );

	printTestStart("writeFloat(), readFloat()");
	m.writeFloat(0,10.1);
	float f = m.readFloat(0);
	printTestResult( (f < 10.100001) && (f > 10.099999) );

	printTestStart("writeBool(), readBool()");
	m.writeBool(0,true);
	printTestResult( m.readBool(0) );

	printTestStart("writeSByte(), readSByte()");
	m.writeSByte(0,-20);
	printTestResult( m.readSByte(0) == -20 );

	printTestStart("load()");
	success = true;
	std::stringstream s;
	for ( unsigned char i= 0; i < 100; i++ ) s << i;
	m.resize(100);
	m.load(s);
	for ( unsigned char i= 0; i < 100; i++ ) if ( m.readByte(i) != i ) success = false;
	printTestResult( success );

	printTestStart("save()");
	for ( unsigned char i= 0; i < 100; i++ ) m.writeByte(i,i);
	success = true;
	std::stringstream s2;
	m.save(s2);

	for ( unsigned char i = 0; i < 100; i++ ) {
		if ( s2.get() != i )
			success = false;
	}
	printTestResult( success );


	printTestResult();
}
