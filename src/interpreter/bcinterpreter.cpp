#include "bcinterpreter.h"

#include <stdexcept>
#include <iostream>

#include <interpreter/vm.h>

namespace interpreter
{

BCInterpreter::BCInterpreter()
{
	//ctor
}

BCInterpreter::~BCInterpreter()
{
	//dtor
}

void BCInterpreter::executeNext( VM& vm )
{
	try {



	} catch ( std::exception& e ) {
		std::cout << "Exception in BCInterpreter::executeNext(VM): " << e.what() << std::endl;
	}
}

void BCInterpreter::reset( VM& vm )
{
	vm.setPC( 0 );
}

}
