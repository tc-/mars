
#include <assert.h>

#include "vm.h"
#include "memory.h"


VM::VM( Interpreter& interpreter, Memory& memory, Stack& stack, unsigned int cpu_speed ) :
  m_interpreter(interpreter),
  m_memory(&memory),
  m_stack(&stack),
  m_speed(cpu_speed),
  m_pc(0)
{
}

VM::~VM()
{
}


void VM::setCPUSpeed( unsigned int new_speed )
{
}

unsigned int VM::getCPUSpeed()
{
}


IO& VM::getIO( unsigned int port )
{
	assert(false);
}

void VM::setIO( unsigned int port, IO& io )
{
}


Memory& VM::memory()
{
	return *m_memory;
}

Stack& VM::stack()
{
	return *m_stack;
}


unsigned int VM::getPC()
{
	return m_pc;
}


void VM::setPC( unsigned int pc )
{
	m_pc = pc;
}
