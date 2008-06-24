#include "menuwindow.h"
#include "cursescolors.h"

namespace cursesclient
{

MenuWindow::MenuWindow( Menu* menu )
{
	setMenu(menu);
}

MenuWindow::~MenuWindow()
{

}


void MenuWindow::repaint()
{
	box(m_win, 0, 0);
	wattron(m_win, COLOR_PAIR(COLOR_MENU_ITEM));

	if ( m_menu != 0 ) {

		std::list<MenuItem*>::iterator it;
		int i = 0;
		for ( it = m_menu->m_items.begin(); it != m_menu->m_items.end(); it++ ) {
			i += 2;
			(*it)->draw( m_win, m_x+2, m_y+i );
		}

	}

	wattroff(m_win, COLOR_PAIR(COLOR_MENU_ITEM));

	wrefresh(m_win);
	CursesWindow::repaint();

}

}

