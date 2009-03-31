#ifndef BOT_H_INCLUDED
#define BOT_H_INCLUDED

#include <vector>

#include "vm/coreio.h"
#include "util/position.h"
#include "bot/botspec.h"
#include "vm/io.h"

typedef unsigned int BotID;

namespace bot
{

class Bot
{

	public:

		Bot( Position& pos, BotSpec& spec ):m_pos(pos){ m_id = getBotID(); loadBotSpec(spec); }

    void update();

		static vm::IOFactory s_iof;

	private:

    void loadBotSpec( BotSpec& spec );

		vm::CoreIO* m_core;
		BotID m_id;
		Position m_pos;

		static void setupIOFactory();
		static BotID s_lastBotID;
		static BotID getBotID() { return ++s_lastBotID; }

};

}

#endif // BOT_H_INCLUDED
