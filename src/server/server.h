#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <stdexcept>


struct ServerStartupArgs
{
    ServerStartupArgs();
    void setArgs( int argc, char** argv ) throw (std::invalid_argument);
    std::string configFile;
    bool runAsDaemon;
    bool isOk;
};


class Server
{
  public:
    Server( const ServerStartupArgs& args );
    ~Server();

    void mainloop();

  protected:
  private:
};

#endif // SERVER_H
