
#include "stack.h"
#include "memory.h"

namespace bot
{

Stack::Stack( Memory& memory, unsigned int base_address ) :
  m_memory(&memory),
  m_base(base_address),
  m_sp(base_address)
{
}

Stack::~Stack()
{
	//dtor
}


void Stack::pushChar( const char& data )
{
	m_memory->writeChar( m_sp, data );
	m_sp += sizeof(char);
}

void Stack::pushInt( const int& data )
{
	m_memory->writeInt( m_sp, data );
	m_sp += sizeof(int);
}

void Stack::pushUInt( const unsigned int& data )
{
	m_memory->writeUInt( m_sp, data );
	m_sp += sizeof(unsigned int);
}

void Stack::pushFloat( const float& data )
{
	m_memory->writeFloat( m_sp, data );
	m_sp += sizeof(float);
}


char Stack::popChar()
{
	m_sp -= sizeof(char);
	return m_memory->readChar(m_sp);
}

int Stack::popInt()
{
	m_sp -= sizeof(int);
	return m_memory->readInt(m_sp);
}

unsigned int Stack::popUInt()
{
	m_sp -= sizeof(unsigned int);
	return m_memory->readUInt(m_sp);
}

float Stack::popFloat()
{
	m_sp -= sizeof(float);
	return m_memory->readFloat(m_sp);
}


void Stack::moveSP( int delta )
{
	// TODO: overflow, underflow checking.
	m_sp += delta;
}

unsigned int Stack::sp()
{
	return m_sp;
}

unsigned int Stack::base()
{
	return m_base;
}

}
