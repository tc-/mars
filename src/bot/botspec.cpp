#include "botspec.h"


namespace bot
{


BotSpec::BotSpec( const std::string& specFile )
{
  loadFromFile( specFile );
}

BotSpec::~BotSpec()
{
}


void BotSpec::loadFromFile( const std::string& specFile )
{

  m_config.readFile(specFile.c_str());

}


}
