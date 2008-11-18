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

    std::string generateUnitCode();

    bool isOk() { return m_ok; }

    Setting& root() { return *m_root; }
    Setting& parts() { return *m_parts; }

  protected:

    bool m_ok;
    Setting* m_parts;
    Setting* m_root;
    Config m_config;

  private:
};


}

#endif // BOTSPEC_H
