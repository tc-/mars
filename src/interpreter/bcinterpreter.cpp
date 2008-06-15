#include "bcinterpreter.h"

#include <stdexcept>
#include <iostream>

#include <interpreter/vm.h>
#include <bot/memory.h>
#include <bot/stack.h>

#define NOP_GROUP 0
#define CONST_GROUP 1
#define ILOAD_GROUP 2
#define ISTOR_GROUP 3
#define GOTO_GROUP 4
#define IOPS1_GROUP 5
#define IOPS2_GROUP 6
#define BRA1_GROUP 7
#define BRA2_GROUP 8
#define STACK_GROUP 9
#define LOGIC_GROUP 10
#define CALL_GROUP 11
#define MEM_GROUP 12
#define PORT_GROUP 13
// ...
#define EXT_GROUP 63

using namespace bot;

namespace interpreter
{

BCInterpreter::BCInterpreter()
{
}

BCInterpreter::~BCInterpreter()
{
}

void BCInterpreter::executeNext( VM& vm )
{
/*	try {

		vmUInt pc = vm.getPC();
		vmByte op = vm.memory().readByte( pc++ );

		executeOp( op, pc, vm );

	} catch ( std::exception& e ) {
		std::cout << "Exception in BCInterpreter::executeNext(VM): " << e.what() << std::endl;
	}*/
}

void BCInterpreter::reset( VM& vm )
{
//	vm.setPC( 0 );
}
/*
void BCInterpreter::executeOp( const unsigned char& op, unsigned int& pc, VM& vm)
{
	unsigned char opgroup = op >> 2;
	unsigned char subop = op & 0x03;

	switch ( opgroup ) {

		case CONST_GROUP : executeCONST(subop, pc, vm); break;

		case ILOAD_GROUP : executeILOAD(subop, pc, vm); break;

		case ISTOR_GROUP : executeISTOR(subop, pc, vm); break;

		case GOTO_GROUP : executeGOTO(subop, pc, vm); break;

		case IOPS2_GROUP : subop |= 0x04;
		case IOPS1_GROUP : executeIOPS(subop, pc, vm); break;

		case BRA2_GROUP : subop |= 0x04;
		case BRA1_GROUP : executeBRA(subop, pc, vm); break;

		case STACK_GROUP : executeSTACK(subop, pc, vm); break;

		case LOGIC_GROUP : executeLOGIC(subop, pc, vm); break;

		case CALL_GROUP : executeCALL(subop, pc, vm); break;

		case MEM_GROUP : executeMEM(subop, pc, vm); break;

		case PORT_GROUP : executePORT(subop, pc, vm); break;

		case EXT_GROUP : executeEXT(subop, pc, vm); break;

		case NOP_GROUP : ;
		default: break;
	}

	vm.cyclesExecuted(1);
}

void BCInterpreter::executeCONST( const unsigned char& subop, unsigned int& pc, VM& vm)
{
	switch ( subop ) {
		case 0: // iconst
			vm.stack().pushInt( vm.memory().readInt( pc ) );
			pc += sizeof(vmInt);
			vm.cyclesExecuted(2);
			break;

		case 1: // iconst_0
			vm.stack().pushInt(0);
			pc += sizeof(vmInt);
			vm.cyclesExecuted(2);
			break;

		case 2: // iconst_1
			vm.stack().pushInt(1);
			pc += sizeof(vmInt);
			vm.cyclesExecuted(2);
			break;

		case 3: // iconst_m1
			vm.stack().pushInt(-1);
			pc += sizeof(vmInt);
			vm.cyclesExecuted(2);
			break;

		default: throw std::invalid_argument("executeCONST(): invalid subop"); break;
	}
}

void BCInterpreter::executeILOAD( const unsigned char& subop, unsigned int& pc, VM& vm)
{
	switch ( subop ) {
		case 0: break;
		case 1: break;
		case 2: break;
		case 3: break;
		default: throw std::invalid_argument("executeILOAD(): invalid subop"); break;
	}
}

void BCInterpreter::executeISTOR( const unsigned char& subop, unsigned int& pc, VM& vm)
{
	switch ( subop ) {
		case 0: break;
		case 1: break;
		case 2: break;
		case 3: break;
		default: throw std::invalid_argument("executeISTOR(): invalid subop"); break;
	}
}

void BCInterpreter::executeGOTO( const unsigned char& subop, unsigned int& pc, VM& vm)
{
	switch ( subop ) {
		case 0: break;
		case 1: break;
		case 2: break;
		case 3: break;
		default: throw std::invalid_argument("executeGOTO(): invalid subop"); break;
	}
}

void BCInterpreter::executeIOPS( const unsigned char& subop, unsigned int& pc, VM& vm)
{
	switch ( subop ) {
		case 0: break;
		case 1: break;
		case 2: break;
		case 3: break;
		default: throw std::invalid_argument("executeIOPS(): invalid subop"); break;
	}
}

void BCInterpreter::executeBRA( const unsigned char& subop, unsigned int& pc, VM& vm)
{
	switch ( subop ) {
		case 0: break;
		case 1: break;
		case 2: break;
		case 3: break;
		default: throw std::invalid_argument("executBRA(): invalid subop"); break;
	}
}

void BCInterpreter::executeSTACK( const unsigned char& subop, unsigned int& pc, VM& vm)
{
	switch ( subop ) {
		case 0: break;
		case 1: break;
		case 2: break;
		case 3: break;
		default: throw std::invalid_argument("executeSTACK(): invalid subop"); break;
	}
}

void BCInterpreter::executeLOGIC( const unsigned char& subop, unsigned int& pc, VM& vm)
{
	switch ( subop ) {
		case 0: break;
		case 1: break;
		case 2: break;
		case 3: break;
		default: throw std::invalid_argument("executeLOGIC(): invalid subop"); break;
	}
}

void BCInterpreter::executeCALL( const unsigned char& subop, unsigned int& pc, VM& vm)
{
	switch ( subop ) {
		case 0: break;
		case 1: break;
		case 2: break;
		case 3: break;
		default: throw std::invalid_argument("executeCALL(): invalid subop"); break;
	}
}

void BCInterpreter::executeMEM( const unsigned char& subop, unsigned int& pc, VM& vm)
{
	switch ( subop ) {
		case 0: // imemstor
			vm.memory().writeInt( vm.memory().readUInt(pc), vm.stack().popInt() );
			pc += sizeof(vmInt);
			vm.cyclesExecuted(3);
			break;

		case 1: // imemload
			vm.stack().pushInt( vm.memory().readInt( vm.memory().readUInt(pc) ) );
			pc += sizeof(vmInt);
			vm.cyclesExecuted(3);
			break;

		case 2: break;
		case 3: break;
		default: throw std::invalid_argument("executeMEM(): invalid subop"); break;
	}
}

void BCInterpreter::executePORT( const unsigned char& subop, unsigned int& pc, VM& vm)
{
	switch ( subop ) {
		case 0: break;
		case 1: break;
		case 2: break;
		case 3: break;
		default: throw std::invalid_argument("executePORT(): invalid subop"); break;
	}
}

void BCInterpreter::executeEXT( const unsigned char& subop, unsigned int& pc, VM& vm)
{
	switch ( subop ) {
		case 0: break;
		case 1: break;
		case 2: break;
		case 3:
			if ( vm.memory().readByte(pc) != 255 ) pc++;
			break;
		default: throw std::invalid_argument("executeEXT(): invalid subop"); break;
	}
}
*/

}
