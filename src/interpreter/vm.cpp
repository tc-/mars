
#include <assert.h>

#include "vm.h"
#include "bot/memory.h"
#include "bot/stack.h"
#include "interpreter.h"

namespace interpreter
{

VM::VM( Interpreter& interpreter, Memory& memory, Stack& stack, unsigned int cpu_speed ) :
  m_interpreter(interpreter),
  m_memory(memory),
  m_stack(stack),
  m_speed(cpu_speed),
  m_pc(0),
  m_time_left(0)
{
}

VM::~VM()
{
}


void VM::update()
{
	m_time_left += m_speed;
	while ( m_time_left > 0 ) {
		m_time_left--;
		m_interpreter.executeNext( *this );
	}
}


void VM::cyclesExecuted( int num )
{
	m_time_left -= num;
}


void VM::setCPUSpeed( unsigned int new_speed )
{
	m_speed = new_speed;
}


unsigned int VM::getCPUSpeed()
{
	return m_speed;
}


/*
IO& VM::getIO( unsigned int port )
{

}

void VM::setIO( unsigned int port, IO& io )
{
}
*/


Memory& VM::memory()
{
	return m_memory;
}


Stack& VM::stack()
{
	return m_stack;
}


unsigned int VM::getPC()
{
	return m_pc;
}


void VM::setPC( unsigned int pc )
{
	m_pc = pc;
}

}
