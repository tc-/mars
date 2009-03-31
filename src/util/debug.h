#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include <iostream>
#include <stdexcept>


#ifdef DEBUG

#define assert(cond,msg) doAssert(cond,msg)

#else

#define assert(cond,msg)

#endif


inline void debugMessage( const char* msg )
{
  std::cout << "--- " << msg << std::endl;
}


inline void debugMessage( const std::string& msg )
{
  std::cout << "--- " << msg << std::endl;
}


inline void doAssert( const bool& cond, const char* msg )
{
  if ( !cond ) {
    std::cout << "### " << msg << std::endl;
    throw std::runtime_error(msg);
  }
}


inline void doAssert( const bool& cond, const std::string& msg )
{
  if ( !cond ) {
    std::cout << "### " << msg << std::endl;
    throw std::runtime_error(msg);
  }
}


#endif // DEBUG_H
