#include "curseswindow.h"

#include <stdexcept>

namespace cursesclient
{

CursesWindow::CursesWindow()
{
	m_min_width = 10;
	m_min_height = 10;
	m_updated = false;
	m_win = 0;
	m_width = 0;
	m_height = 0;
	m_x = 0;
	m_y = 0;
}

CursesWindow::CursesWindow( const int& width, const int& height, const int& x, const int& y )
{
	m_min_width = 10;
	m_min_height = 10;
	m_updated = false;
	m_win = 0;
	boundry( width, height, x, y );
}


CursesWindow::~CursesWindow()
{
	destroyWin();
}


void CursesWindow::destroyWin()
{
	if ( m_win != 0 ) {
		wborder(m_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
		wrefresh(m_win);
		delwin(m_win);
	}
	m_win = 0;
}


void CursesWindow::repaint()
{
	wmove(m_win,0 ,0);
	wrefresh(m_win);
	m_updated = true;
}


bool CursesWindow::updated()
{
	if ( m_updated ) {
		m_updated = false;
		return true;
	}
	return false;
}


void CursesWindow::resize( const int& width, const int& height )
{
	boundry( width, height, getXPos(), getYPos() );
}


void CursesWindow::move( const int& x, const int& y)
{
	boundry( getWidth(), getHeight(), x, y );
}


void CursesWindow::boundry( const int& width, const int& height, const int& x, const int& y )
{
	destroyWin();
	m_win = newwin(height, width, y, x);
	//box(m_win, 0 , 0);
	wrefresh(m_win);
	m_width = width;
	m_height = height;
	m_x = x;
	m_y = y;
}


int CursesWindow::getWidth()
{
	return m_width;
}


int CursesWindow::getHeight()
{
	return m_height;
}


int CursesWindow::getXPos()
{
	return m_x;
}


int CursesWindow::getYPos()
{
	return m_y;
}

}
