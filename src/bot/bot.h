#ifndef BOT_H_INCLUDED
#define BOT_H_INCLUDED

#include <vector>

#include "vm/coreio.h"
#include "util/position.h"
#include "bot/botspec.h"
#include "vm/io.h"

typedef unsigned int BotId;

namespace bot
{

class Bot
{

	public:

		Bot( BotId id, Position& pos, BotSpec& spec ):m_id(id),m_pos(pos){ loadBotSpec(spec); }

    void update();

	private:

    void loadBotSpec( BotSpec& spec );

		vm::CoreIO* m_core;
		BotId m_id;
		Position m_pos;

		static vm::IOFactory s_iof;
		static void setupIOFactory();

};

}

#endif // BOT_H_INCLUDED
