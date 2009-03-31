
#include "bot.h"
#include "vm/coreio.h"
#include "bot/engineio.h"
#include "util/debug.h"

namespace bot
{


vm::IOFactory Bot::s_iof;


void Bot::update()
{
  m_core->update(*this);
}


void Bot::loadBotSpec( BotSpec& spec )
{
  assert( spec.isOk(), "Bot::loadBotSpec( BotSpec& spec ): Spec not Ok." );
  m_core = (vm::CoreIO*)vm::CoreIO::createCoreIOPart( spec.root() );

  for ( int i = 0; i < spec.parts().getLength(); i++ ) {
    Setting& s = spec.parts()[i];
    m_core->addIO(s);
  }
}


void Bot::setupIOFactory()
{
  s_iof.addIOClass( "Null", vm::NullIO::createIOPart );
  s_iof.addIOClass( "TrackedEngine", bot::TrackedEngineIO::createIOPart );
}


}
