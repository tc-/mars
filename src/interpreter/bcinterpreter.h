#ifndef BCINTERPRETER_H
#define BCINTERPRETER_H

#include <interpreter/interpreter.h>

namespace interpreter
{

class VM;

class BCInterpreter : public Interpreter
{
	public:

		BCInterpreter();
		virtual ~BCInterpreter();

		void executeNext( VM& vm );
		void reset( VM& vm );

	private:

		void executeOp( const unsigned char& op, unsigned int& pc, VM& vm);

		void executeCONST( const unsigned char& subop, unsigned int& pc, VM& vm);
		void executeILOAD( const unsigned char& subop, unsigned int& pc, VM& vm);
		void executeISTOR( const unsigned char& subop, unsigned int& pc, VM& vm);
		void executeGOTO( const unsigned char& subop, unsigned int& pc, VM& vm);
		void executeIOPS( const unsigned char& subop, unsigned int& pc, VM& vm);
		void executeBRA( const unsigned char& subop, unsigned int& pc, VM& vm);
		void executeSTACK( const unsigned char& subop, unsigned int& pc, VM& vm);
		void executeLOGIC( const unsigned char& subop, unsigned int& pc, VM& vm);
		void executeCALL( const unsigned char& subop, unsigned int& pc, VM& vm);
		void executeMEM( const unsigned char& subop, unsigned int& pc, VM& vm);
		void executePORT( const unsigned char& subop, unsigned int& pc, VM& vm);
		void executeEXT( const unsigned char& subop, unsigned int& pc, VM& vm);


};

}

#endif // BCINTERPRETER_H
