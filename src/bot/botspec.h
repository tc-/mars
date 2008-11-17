#ifndef BOTSPEC_H
#define BOTSPEC_H

#include <string>
#include <vector>
#include <libconfig.h++>

using namespace libconfig;

namespace bot
{

class BotSpec
{
  public:

    BotSpec( const std::string& specFile );
    ~BotSpec();

    void loadFromFile( const std::string& specFile );

    inline std::string& modelName()  { return m_model; }
    inline Setting& parts() { return *m_parts; }

  protected:

    std::string m_model;
    Setting* m_parts;
    Config m_config;

  private:
};


}

#endif // BOTSPEC_H
