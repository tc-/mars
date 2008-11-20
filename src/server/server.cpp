#include "server.h"
#include <iostream>


#define DEFAULT_SERVER_CONFIG_FILE "server.conf"


Server::Server( const ServerStartupArgs& args )
{

}

Server::~Server()
{

}


void Server::mainloop()
{

}



ServerStartupArgs::ServerStartupArgs()
{
  runAsDaemon = false;
  configFile = DEFAULT_SERVER_CONFIG_FILE;
}

void ServerStartupArgs::setArgs( int argc, char** argv ) throw (std::invalid_argument)
{
  ServerStartupArgs();
  std::string last = "";
  for ( int i = 0; i < argc; i++ ) {
    std::string arg = argv[i];
    if ( last == "" ) {
      if ( ( arg == "") || (arg == " ") || (arg == "\t") ) {
        continue;
      } else if ( arg == "-d" ) {
        runAsDaemon = true;
      } else if ( arg == "-c" ) {
        last = arg;
      } else {
        std::string msg = "Invalid parameter: " + arg + ".";
        throw std::invalid_argument(msg);
      }

    } else {
      last = "";
      if ( last == "-c" ) configFile = arg;
    }
  }
  if ( last != "" ) {
    std::string msg = "Parameter " + last + " expects a parameter to follow.";
    throw std::invalid_argument(msg);
  }
}

