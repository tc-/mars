#ifndef VM_H
#define VM_H

#include "vm/memory.h"


namespace vm
{


enum Interrupts
{
	intDivideByZero=0,
	intSoftware=1
};

#define numInterruptVectors 2


class CoreIO;

class VM
{
	public:


		VM( Memory& memory, unsigned int cpu_speed, unsigned int sp, CoreIO& coreio );
		virtual ~VM();

		void update();

		inline void setTimeLeftD( int delta ) { m_time_left += delta; }

		inline void setCPUSpeed( unsigned int new_speed ) { m_speed = new_speed; }
		inline unsigned int getCPUSpeed() { return m_speed; }

		inline unsigned int getPC() { return m_pc; }
		inline void setPC( unsigned int pc ) { m_pc = pc<m_memory.size()?pc:0; }

		inline unsigned int getSP() { return m_sp; }
		inline void setSP( unsigned int sp ) { m_sp = sp<m_memory.size()?sp:0; }

		void reset( unsigned int pc, unsigned int sp );

		void interrupt( Interrupts interrupt );

		void step();
		void step( unsigned int steps );
		void printState();

		void load( std::istream& data );
		void save( std::ostream& data );

		IO& getIO( unsigned int address );

		Memory& memory() { return m_memory; }

	protected:

    CoreIO& m_coreio;
		Memory& m_memory;
		unsigned int m_speed;
		unsigned int m_pc;
		unsigned int m_sp;
		unsigned int m_bos;
		int m_time_left;
		vmUInt m_ints[numInterruptVectors];
};

}

#endif // VM_H
