
#include <iostream>
#include "memory.h"

int main( int argc, char** argv )
{
	std::cout << "test" << std::endl;

	Memory m(10);
	m.clear();

	m.writeChar( 0, 'a' );
	std::cout << m.readChar(0);

	m.writeInt(1,-10);
	std::cout << m.readInt(1);

	return 0;
}
