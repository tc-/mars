#ifndef BCINTERPRETER_H
#define BCINTERPRETER_H

#include <interpreter/interpreter.h>

class VM;

namespace interpreter
{

class BCInterpreter : public Interpreter
{
	public:

		BCInterpreter();
		virtual ~BCInterpreter();

		void executeNext( VM& vm );
		void reset( VM& vm );

	private:
};

}

#endif // BCINTERPRETER_H
