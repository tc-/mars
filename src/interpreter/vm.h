#ifndef VM_H
#define VM_H

class Memory;
class Stack;
class IO;

namespace interpreter
{

class Interpreter;

class VM
{
	public:

		VM( Interpreter& interpreter, Memory& memory, Stack& stack, unsigned int cpu_speed );
		virtual ~VM();

		void update();

		void setCPUSpeed( unsigned int new_speed );
		unsigned int getCPUSpeed();

		Memory& memory();
		Stack& stack();

		IO& getIO( unsigned int port );
		void setIO( unsigned int port, IO& io );

		unsigned int getPC();
		void setPC( unsigned int pc );

		void cyclesExecuted( int num );

	protected:

		Interpreter& m_interpreter;
		Memory& m_memory;
		Stack& m_stack;
		unsigned int m_speed;
		unsigned int m_pc;
		unsigned int m_time_left;

};

}

#endif // VM_H
