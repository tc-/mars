#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include "curseswindow.h"
#include <string>
#include <curses.h>

namespace cursesclient
{


class MapWindow : public CursesWindow
{
	public:
		MapWindow();
		~MapWindow();

		void repaint();

	protected:

};

}

#endif // MENUWINDOW_H
