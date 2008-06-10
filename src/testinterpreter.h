#ifndef TESTINTERPRETER_H
#define TESTINTERPRETER_H

#include "interpreter.h"

class TestInterpreter : public Interpreter
{
	public:

		TestInterpreter();

		~TestInterpreter();

		void executeNext( VM& vm );
		void reset( VM& vm );
};

#endif // TESTINTERPRETER_H
