#ifndef STACK_H
#define STACK_H

#include "io.h"

namespace bot
{

class Memory;

class Stack : public IO
{
	public:

		Stack( Memory& memory, unsigned int base_address );
		virtual ~Stack();

		void pushChar( const char& data );
		void pushInt( const int& data );
		void pushUInt( const unsigned int& data );
		void pushFloat( const float& data );

		char popChar();
		int popInt();
		unsigned int popUInt();
		float popFloat();

		void moveSP( int delta );

		unsigned int sp();
		unsigned int base();

	protected:

		Memory* m_memory;
		unsigned int m_base;
		unsigned int m_sp;
};

}

#endif // STACK_H
