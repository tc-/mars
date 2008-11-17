
#include <ctime>

#include "vm/vm.h"
#include "vm/memory.h"

using namespace vm;

void doVMBenchmark();

int main( int argc, char** argv )
{
	std::cout << "######################################" << std::endl;
	std::cout << "## MARS kikkass benchmark executing ##" << std::endl;
	std::cout << "######################################" << std::endl;

	doVMBenchmark();

	return 0;
}


unsigned int counter,testvar;

void incGotoLoop()
{
	for ( int i = 0; i < 100; i++ ) {
		//testvar++;
		counter++;
	}
}


void doVMBenchmark()
{
	int times[10];

	std::cout << std::endl << "*** Doing VM benchmark:" << std::endl;
	std::cout << " - Endless iinc_1,goto_b loop turns in one sec(vm): ";
	std::clock_t endwait;

	for ( int i = 0; i < 10; i++ ) {

		Memory m(13);
		VM vm( m, 100, 8 );

		vm.reset( 0, 8 );

		m.writeByte( 0, 4 ); // iconst 0
		m.writeInt( 1, 0 );

		m.writeByte( 5, 25 ); // iinc_1

		m.writeByte( 6, 16 ); // goto_b -2
		m.writeSByte( 7, -2 );

		endwait = std::clock() + CLOCKS_PER_SEC;
		while ( clock() < endwait ) {
			vm.update();
		}

		times[i] = m.readInt( 8 );

	}

	long int sum = 0;
	for ( int j = 0; j < 10; j++ ) {
		sum += times[j];
	}

	std::cout << ((sum/10)/1000000.0) << " M" << std::endl;

	std::cout << " - Endless iinc_1,goto_b loop turns in one sec(cpu): ";

	endwait = std::clock() + CLOCKS_PER_SEC;
	counter = 0;
	while ( clock() < endwait ) {
		incGotoLoop();
	}

	std::cout << (counter/1000000.0) << " M" << std::endl;

	std::cout << "Benchmark [ Done ]." << std::endl;
}


