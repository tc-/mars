#ifndef BOT_H_INCLUDED
#define BOT_H_INCLUDED

#include <vector>

#include "vm/vm.h"
#include "util/position.h"
#include "bot/botspec.h"

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

		vm::VM* m_vm;
		BotId m_id;
		Position m_pos;

};

}

#endif // BOT_H_INCLUDED
