
#include <iostream>
#include "server.h"

int main( int argc, char** argv )
{
  ServerStartupArgs args;
  try
  {
    args.setArgs( argc, argv );
  } catch ( std::invalid_argument& e ) {
    std::cout << "!!! " << e.what() << std::endl;
    return 1;
  }

  try
  {
    Server server( args );

    std::cout << "*** Entering mainloop." << std::endl;
    server.mainloop();

  } catch ( std::exception& e ) {
    std::cout << "!!! main(): exception: " << e.what() << __LINE__ << std::endl;
    return 1;
  } catch (...) {
    std::cout << "!!! main(): unknown exception!" << std::endl;
    return 1;
  }

  std::cout << "*** Quit." << std::endl;
	return 0;
}
