#ifndef INTERPRETER_H
#define INTERPRETER_H

class VM;

class Interpreter
{
	public:

		virtual void executeNext( VM& vm ) = 0;

};

#endif // INTERPRETER_H
