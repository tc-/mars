
#include <fstream>

#include "vm/vm.h"
#include "bot/memory.h"
#include "testlib.h"

using namespace vm;
using namespace bot;
using namespace test;

void testInstructionsICONST();
void testInstructionsILOAD();
void testInstructionsSTACK();
void testInstructionsJUMP();
void testInstructionsIOPS();
void testInstructionsCMP();

void doVMBenchmark();
//void testDisasm();

bool readInt( Memory& m, unsigned int index,  int expect );

void testVM()
{
	bool success;
	printTestName("VM class");

	printTestStart("Constructor()");
	Memory m(10);
	m.clear();
	VM vm( m, 1, 6 ); // sp = 6
	printTestResult( (vm.getSP() == 6) && (vm.getCPUSpeed() == 1) && (vm.getPC() == 0) );

	printTestStart("reset(pc,sp)");
	vm.reset( 1, 5 );
	printTestResult( (vm.getSP() == 5) && (vm.getPC() == 1) );

	printTestStart("setSP()");
	success = true;
	vm.setSP(0);
	if (vm.getSP() != 0) success = false;
	vm.setSP(10);
	if (vm.getSP() != 0) success = false;
	printTestResult( success );

	printTestStart("setPC()");
	success = true;
	vm.setPC(0);
	if (vm.getPC() != 0) success = false;
	vm.setPC(10);
	if (vm.getPC() != 0) success = false;
	printTestResult( success );

	printTestStart("load()");
	success =true;
	try {
		std::ifstream f("test/loadfiles/looptest.bot", std::ifstream::in);
		vm.load(f);
	} catch ( std::exception& e ) {
		printException(e);
	}
	vm.step(4);
	if ( !readInt(m, 4, 2) ) success = false;

	printTestResult( success );

	printTestResult();

	testInstructionsICONST();
	testInstructionsILOAD();
	testInstructionsSTACK();
	testInstructionsJUMP();
	testInstructionsIOPS();
	testInstructionsCMP();
  //testDisasm();
}

/*void testDisasm()
{
	Memory m(100);
	VM vm( m, 1, 6 );
	m.writeByte( 0, 0 );
	m.writeByte( 1, 4 );
	m.writeInt( 2, 60 );
	m.writeByte( 6, 5 );
	m.writeByte( 7, 6 );
	m.writeByte( 8, 7 );
	m.writeByte( 9, 127 );

	std::cout << m.disasm().c_str();
}*/


bool vmState( VM& vm, unsigned int pc, unsigned int sp )
{
	if (( pc == vm.getPC() ) && ( sp == vm.getSP() )) {
		return true;
	} else {
		std::cout << "(pc:" << vm.getPC() << "(" << pc << ") sp:" << vm.getSP() << "(" << sp << ")) ";
		return false;
	}
}

bool readInt( Memory& m, unsigned int index,  int expect )
{
	if ( m.readInt(index) == expect ) {
		return true;
	} else {
		std::cout << "(m(" << index << ")=" << m.readInt(index) << "(" << expect << ")) ";
		return false;
	}
}

bool readSByte( Memory& m, unsigned int index,  signed char expect )
{
	if ( m.readSByte(index) == expect ) {
		return true;
	} else {
		std::cout << "(m(" << index << ")=" << (int)m.readSByte(index) << "(" << (int)expect << ")) ";
		return false;
	}
}

void testInstructionsICONST()
{
	bool success;
	printTestName("ICONST instructions");

	Memory m(100);
	VM vm( m, 1, 6 );

	printTestStart("iconst");
	success = true;
	m.clear();
	vm.reset(0,6);
	m.writeByte(0,4);
	m.writeInt(1,100);
	vm.update();
	if ( !vmState(vm,5,10) || !readInt(m,6,100) ) success = false;

	m.writeByte(98,4);
	m.writeInt(6,500);
	vm.reset(98,6);
	vm.update();
	if ( !vmState(vm,0,10) || !readInt(m,6,0) ) success = false;
	printTestResult( success );

	printTestStart("iconst_0");
	success = true;
	m.clear();
	vm.reset(0,6);
	m.writeByte(0,5);
	m.writeInt(6,100);
	vm.update();
	if ( !vmState(vm,1,10) || !readInt(m,6,0) ) success = false;
	printTestResult( success );

	printTestStart("iconst_1");
	success = true;
	m.clear();
	vm.reset(0,6);
	m.writeByte(0,6);
	m.writeInt(6,100);
	vm.update();
	if ( !vmState(vm,1,10) || !readInt(m,6,1) ) success = false;
	printTestResult( success );

	printTestStart("iconst_m1");
	success = true;
	m.clear();
	vm.reset(0,6);
	m.writeByte(0,7);
	m.writeInt(6,100);
	vm.update();
	if ( !vmState(vm,1,10) || !readInt(m,6,-1) ) success = false;
	printTestResult( success );

	printTestResult();
}


void testInstructionsILOAD()
{
	bool success;
	printTestName("ILOAD instructions");

	Memory m(100);
	VM vm( m, 1, 10 );

	printTestStart("iload_b");
	success = true;
	m.clear();
	vm.reset(0,6);
	vm.setSP(10);
	m.writeByte(0,8);
	m.writeSByte(1, 4);
	m.writeInt(6,100);
	vm.update();
	if ( !vmState(vm,2,14) || !readInt(m,10,100) ) success = false;
	printTestResult( success );

	printTestStart("iload");
	success = true;
	m.clear();
	vm.reset(0,6);
	vm.setSP(10);
	m.writeByte(0,9);
	m.writeInt(1,0);
	m.writeInt(6,100);
	vm.update();
	if ( !vmState(vm,5,14) || !readInt(m,10,100) ) success = false;
	printTestResult( success );

	printTestResult();
}


void testInstructionsISTOR()
{
	/*bool success;
	printTestName("ISTOR instructions");

	Memory m(100);
	VM vm( m, 1, 10 );

	printTestStart("istor_b");
	success = true;
	m.clear();
	vm.reset(0,6);
	vm.setSP(14);
	m.writeByte(0,12);
	m.writeSByte(1,8);
	m.writeInt(10,100);
	vm.update();
	if ( !vmState(vm,2,14) || !readInt(m,6,100) ) success = false;
	printTestResult( success );

	printTestStart("istor");
	success = true;
	m.clear();
	vm.reset(0,6);
	vm.setSP(14);
	m.writeByte(0,12);
	m.writeSByte(1,8);
	m.writeInt(10,100);
	vm.update();
	if ( !vmState(vm,5,14) || !readInt(m,6,100) ) success = false;
	printTestResult( success );

	printTestResult();*/
}


void testInstructionsSTACK()
{
	bool success;
	printTestName("STACK instructions");

	Memory m(100);
	VM vm( m, 1, 10 );

	printTestStart("pop");
	success = true;
	m.clear();
	vm.reset(0,6);
	vm.setSP(10);
	m.writeByte(0,36);
	vm.update();
	if ( !vmState(vm,1,9) ) success = false;
	printTestResult( success );

	printTestStart("pop_4");
	success = true;
	m.clear();
	vm.reset(0,6);
	vm.setSP(10);
	m.writeByte(0,37);
	vm.update();
	if ( !vmState(vm,1,6) ) success = false;
	printTestResult( success );

	printTestStart("incsp(+)");
	success = true;
	m.clear();
	vm.reset(0,6);
	vm.setSP(10);
	m.writeByte(0,38);
	m.writeSByte(1,5);
	vm.update();
	if ( !vmState(vm,2,15) ) success = false;
	printTestResult( success );

	printTestStart("incsp(-)");
	success = true;
	m.clear();
	vm.reset(0,6);
	vm.setSP(10);
	m.writeByte(0,38);
	m.writeSByte(1,-4);
	vm.update();
	if ( !vmState(vm,2,6) ) success = false;
	printTestResult( success );


	printTestResult();
}


void testInstructionsJUMP()
{
	bool success;
	printTestName("JUMP instructions");

	Memory m(100);
	VM vm( m, 1, 10 );

	printTestStart("goto_b");
	success = true;
	m.clear();
	vm.reset(0,6);
	m.writeByte(0,16);
	m.writeSByte(1,5);
	vm.update();
	if ( !vmState(vm,6,6) ) success = false;
	printTestResult( success );

	printTestStart("goto");
	success = true;
	m.clear();
	vm.reset(0,6);
	m.writeByte(0,17);
	m.writeInt(1,5);
	vm.update();
	if ( !vmState(vm,6,6) ) success = false;
	printTestResult( success );

	printTestStart("jump");
	success = true;
	m.clear();
	vm.reset(0,6);
	m.writeByte(0,18);
	m.writeUInt(1,6);
	vm.update();
	if ( !vmState(vm,6,6) ) success = false;
	printTestResult( success );

	printTestResult();
}


void testInstructionsIOPS()
{
	bool success;
	printTestName("IOPS instructions");

	Memory m(100);
	VM vm( m, 1, 10 );

	printTestStart("iadd");
	success = true;
	m.clear();
	vm.reset(0,6);
	m.writeByte(0,20);
	m.writeInt(6,10);
	m.writeInt(10,20);
	vm.setSP(14);
	vm.update();
	if ( !vmState(vm,1,10) || !readInt(m,6,30) ) success = false;
	printTestResult( success );

	printTestStart("imul");
	success = true;
	m.clear();
	vm.reset(0,6);
	m.writeByte(0,21);
	m.writeInt(6,10);
	m.writeInt(10,20);
	vm.setSP(14);
	vm.update();
	if ( !vmState(vm,1,10) || !readInt(m,6,200) ) success = false;
	printTestResult( success );

	printTestStart("idiv");
	success = true;
	m.clear();
	vm.reset(0,6);
	m.writeByte(0,22);
	m.writeInt(6,10);
	m.writeInt(10,10);
	vm.setSP(14);
	vm.update();
	if ( !vmState(vm,1,10) || !readInt(m,6,1) ) success = false;
	printTestResult( success );

	printTestStart("idiv by zero");
	m.clear();
	vm.reset(0,6);
	m.writeByte(0,22);
	m.writeInt(6,10);
	m.writeInt(10,0);
	vm.setSP(14);
	vm.update();
	if ( !vmState(vm,1,10) || !readInt(m,6,INT_MAX) ) success = false;
	printTestResult( success );

	printTestStart("imod");
	success = true;
	m.clear();
	vm.reset(0,6);
	m.writeByte(0,23);
	m.writeInt(6,10);
	m.writeInt(10,3);
	vm.setSP(14);
	vm.update();
	if ( !vmState(vm,1,10) || !readInt(m,6,1) ) success = false;
	printTestResult( success );

	printTestStart("imod by zero");
	m.clear();
	vm.reset(0,6);
	m.writeByte(0,23);
	m.writeInt(6,10);
	m.writeInt(10,0);
	vm.setSP(14);
	vm.update();
	if ( !vmState(vm,1,10) || !readInt(m,6,0) ) success = false;

	printTestResult( success );

	printTestStart("iinc");
	success = true;
	m.clear();
	vm.reset(0,6);
	m.writeByte(0,24);
	m.writeInt(1,10);
	m.writeInt(6,10);
	vm.setSP(10);
	vm.update();
	if ( !vmState(vm,5,10) || !readInt(m,6,20) ) success = false;
	printTestResult( success );

	printTestStart("iinc_1");
	success = true;
	m.clear();
	vm.reset(0,6);
	m.writeByte(0,25);
	m.writeInt(6,10);
	vm.setSP(10);
	vm.update();
	if ( !vmState(vm,1,10) || !readInt(m,6,11) ) success = false;
	printTestResult( success );

	printTestResult();
}

void testInstructionsCMP()
{
	bool success;
	printTestName("CMP instructions");

	Memory m(100);
	VM vm( m, 1, 10 );

	printTestStart("icmp");
	success = true;
	m.clear();
	vm.reset(0,6);
	vm.setSP(14);
	m.writeByte(0,60);
	m.writeInt(6,-100);
	m.writeInt(10,101);
	vm.update();
	if ( !vmState(vm,1,7) || !readSByte(m,6,1) ) success = false;
	printTestResult( success );

	printTestStart("iucmp");
	success = true;
	m.clear();
	vm.reset(0,6);
	vm.setSP(14);
	m.writeByte(0,61);
	m.writeInt(6,100);
	m.writeInt(10,101);
	vm.update();
	if ( !vmState(vm,1,7) || !readSByte(m,6,1) ) success = false;
	printTestResult( success );

	printTestStart("itest");
	success = true;
	m.clear();
	vm.reset(0,6);
	vm.setSP(10);
	m.writeByte(0,62);
	m.writeInt(6,100);
	vm.update();
	if ( !vmState(vm,1,7) || !readSByte(m,6,1) ) success = false;
	printTestResult( success );

	printTestResult();
}

