#ifndef TESTINTERPRETER_H
#define TESTINTERPRETER_H

#include "interpreter/interpreter.h"

using namespace interpreter;

namespace test
{

class TestInterpreter : public Interpreter
{
	public:

		TestInterpreter();

		~TestInterpreter();

		void executeNext( VM& vm );
		void reset( VM& vm );
};

}

#endif // TESTINTERPRETER_H
