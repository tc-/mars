#include "botspec.h"


namespace bot
{


BotSpec::BotSpec( const std::string& specFile )
{
  m_ok = false;
  m_parts = 0;
  m_root = 0;
  loadFromFile( specFile );
}

BotSpec::~BotSpec()
{
}


void BotSpec::loadFromFile( const std::string& specFile )
{
  m_ok = true;
  try
  {
    m_config.readFile(specFile.c_str());
    m_root = &m_config.lookup("botspec");
    m_parts = &m_config.lookup("botspec.parts");
  } catch (...) {
    m_ok = false;
  }

  if ( !m_ok ) {
    m_parts = 0;
    m_root = 0;
  }
}


std::string generateUnitCode()
{
  return "";
}


}
