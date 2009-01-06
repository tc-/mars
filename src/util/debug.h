#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include <stdio.h>
#include <stdexcept>
#define assert(cond,msg) doAssert(cond,msg)


void debugMessage( const char* msg )
{
  std::cout << "ddd " << msg << std::endl;
}


void debugMessage( const std::string& msg )
{
  std::cout << "ddd " << msg << std::endl;
}


inline void doAssert( const bool& cond, const char* msg )
{
  if ( !cond ) {
    debugMessage(msg);
  }
}


inline void doAssert( const bool& cond, const std::string& msg )
{
  if ( !cond ) {
    debugMessage(msg);
    throw std::runtime_error(msg);
  }
}


#endif // DEBUG_H
