
#include <curses.h>

#include "cursesscreen.h"
#include "curseswindow.h"
#include "settings.h"
#include "cursescolors.h"

using namespace client;

namespace cursesclient
{

CursesScreen::CursesScreen()
{
	m_east = 0;
	m_south = 0;
	m_center = 0;

	initscr();

	//!@TODO: warn if we want to use colors but terminal doesn't support it.
	if ( sett().curses_use_colors && has_colors() ) {

		start_color();

		init_pair(COLOR_BLACK, COLOR_BLACK, COLOR_BLACK);
		init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
		init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
		init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
		init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
		init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
		init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
		init_pair(COLOR_MENU_ITEM, COLOR_WHITE, COLOR_RED);
		init_pair(COLOR_MENU_BG, COLOR_BLACK, COLOR_BLACK);

	} else {
		sett().curses_use_colors = false;
	}
}

CursesScreen::~CursesScreen()
{
	endwin();
}

void CursesScreen::repaint()
{
	if ( m_center != 0 ) m_center->repaint();
}

CursesWindow* CursesScreen::getEast()
{
	return m_east;
}

void CursesScreen::setEast(CursesWindow* win)
{
	m_east = win;
	reorder();
}

CursesWindow* CursesScreen::getSouth()
{
	return m_south;
}

void CursesScreen::setSouth(CursesWindow* win)
{
	m_south = win;
	reorder();
}

CursesWindow* CursesScreen::getCenter()
{
	return m_center;
}

void CursesScreen::setCenter(CursesWindow* win)
{
	m_center = win;
	reorder();
}

void CursesScreen::reorder()
{
	if ( m_center != 0 ) {
		m_center->boundry( COLS, LINES, 0, 0 );
	}
	repaint();
}

}
