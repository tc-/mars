#ifndef VM_H
#define VM_H

#include <iostream>

#include "bot/memory.h"

namespace bot {
class IO;
}

using namespace bot;

namespace vm
{

class VM;

typedef void (VM::*interpretFunc)();

enum Interrupts
{
	intDivideByZero=0,
	intSoftware=1
};

#define numInterruptVectors 2

class VM
{
	public:

		VM( Memory& memory, unsigned int cpu_speed, unsigned int sp );
		virtual ~VM();

		void update();

		inline void setCPUSpeed( unsigned int new_speed ) { m_speed = new_speed; }
		inline unsigned int getCPUSpeed() { return m_speed; }

		inline unsigned int getPC() { return m_pc; }
		inline void setPC( unsigned int pc ) { m_pc = pc % m_memory.size(); }

		inline unsigned int getSP() { return m_sp; }
		inline void setSP( unsigned int sp ) { m_sp = sp % m_memory.size(); }

		void reset( unsigned int pc, unsigned int sp );

		void interrupt( Interrupts interrupt );

		void step();
		void step( unsigned int steps );
		void printState();

		void load( std::istream& data );
		void save( std::ostream& data );

	protected:

		Memory& m_memory;
		unsigned int m_speed;
		unsigned int m_pc;
		unsigned int m_sp;
		unsigned int m_bos;
		unsigned int m_time_left;
		vmUInt m_ints[numInterruptVectors];
};

}

#endif // VM_H
