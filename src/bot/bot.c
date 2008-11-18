
#include "bot.h"
#include "vm/coreio.h"
#include "bot/engineio.h"
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

  for ( int i = 0; i < spec.parts().getLength(); i++ ) {
    Setting& s = spec.parts()[i];
    vm::IO* io = s_iof.createIO(s);
    if ( io != 0 ) m_core->addIO(*io);
  }
}


void Bot::setupIOFactory()
{
  s_iof.addIOClass( "Null", vm::NullIO::createIOPart );
  s_iof.addIOClass( "TrackedEngine", bot::TrackedEngineIO::createIOPart );
}


}
