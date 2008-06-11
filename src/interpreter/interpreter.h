#ifndef INTERPRETER_H
#define INTERPRETER_H

namespace interpreter
{

class VM;

class Interpreter
{
	public:

		virtual void executeNext( VM& vm ) = 0;
		virtual void reset( VM& vm ) = 0;

};

}

#endif // INTERPRETER_H
