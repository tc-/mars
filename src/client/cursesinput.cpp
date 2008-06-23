
#include <curses.h>

#include "cursesinput.h"

namespace cursesclient
{

CursesInput::CursesInput()
{
	keypad(stdscr, TRUE);
	nonl();
	cbreak();
	noecho();
}

CursesInput::~CursesInput()
{

}


inputCommand CursesInput::getInputCommand()
{
	return cmdNone;
}

}
