#ifndef BOT_H_INCLUDED
#define BOT_H_INCLUDED

#include "vm/vm.h"

typedef unsigned int BotId;

class Bot
{

	public:

		Bot( VM& vm, BotId id, Position pos ):m_vm(vm),m_id(id),m_pos(pos){}

	private:

		VM& m_vm;
		BotId m_id;
		Position m_pos;

};



#endif // BOT_H_INCLUDED
