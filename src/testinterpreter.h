#ifndef TESTINTERPRETER_H
#define TESTINTERPRETER_H

#include "interpreter.h"

class TestInterpreter : public Interpreter
{
	public:

		TestInterpreter();

		virtual ~TestInterpreter();

		void executeNext( VM& vm );
};

#endif // TESTINTERPRETER_H
