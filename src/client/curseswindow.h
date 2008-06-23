#ifndef CURSESWINDOW_H
#define CURSESWINDOW_H

#include <curses.h>

namespace cursesclient
{

class CursesWindow
{
	public:
		CursesWindow();
		CursesWindow( const int& width, const int& height, const int& x, const int& y );
		virtual ~CursesWindow();

		int getMinWidth() { return m_min_width; }
		int getMinHeight() { return m_min_height; }
		void setMinWidth( const int& min_width ) { m_min_width = min_width; }
		void setMinHeight( const int& min_height ) { m_min_height = min_height; }

		WINDOW* getCursesWindow() { return m_win; }

		virtual void repaint();
		bool updated();

		void resize( const int& width, const int& height );
		void move( const int& x, const int& y);
		void boundry( const int& width, const int& height, const int& x, const int& y );

		int getWidth();
		int getHeight();
		int getXPos();
		int getYPos();

	protected:

		int m_min_width;
		int m_min_height;

		int m_width;
		int m_height;
		int m_x;
		int m_y;

		bool m_updated;

		WINDOW* m_win;

		void destroyWin();
};

}

#endif // CURSESWINDOW_H
