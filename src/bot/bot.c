
#include "bot.h"
#include "vm/coreio.h"
#include <assert.h>

namespace bot
{


vm::IOFactory Bot::s_iof;


void Bot::update()
{
  m_core->update(*this);
}


void Bot::loadBotSpec( BotSpec& spec )
{
  assert( spec.isOk() );
  m_core = (vm::CoreIO*)vm::CoreIO::createCoreIOPart( spec.root() );
}


void Bot::setupIOFactory()
{
  //s_iof.addIOClass( "Core", vm::CoreIO::createCoreIOPart);
}


}
