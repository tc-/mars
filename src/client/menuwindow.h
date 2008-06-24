#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "curseswindow.h"
#include <string>
#include <list>
#include <curses.h>

namespace cursesclient
{

class Menu;
class MenuItem;

class MenuItemAction
{
	virtual void execute( Menu& menu, MenuItem& item ) = 0;
};

class MenuItem
{
	public:

		MenuItem( const std::string& text, MenuItemAction* action ): m_text(text),m_action(action) { }

		virtual void draw( WINDOW* win, const int& x, const int& y ) {
			wmove(win,y,x); waddch(win, ' ');
			for ( unsigned int i = 0; i < m_text.length(); i++ ) waddch(win,m_text[i]);
			waddch(win, ' ');
		}

	protected:

		friend class Menu;
		std::string m_text;
		MenuItemAction* m_action;

};

class Menu
{

	public:
		Menu() {}
		~Menu() { for ( std::list<MenuItem*>::iterator it = m_items.begin(); it != m_items.end(); it++ ) delete *it; }
		void addItem( const std::string& text, MenuItemAction* action ) { m_items.push_back( new MenuItem(text,action ) ); }
	protected:
		friend class MenuWindow;
		std::list<MenuItem*> m_items;
};

class MenuWindow : public CursesWindow
{
	public:
		MenuWindow( Menu* menu = 0 );
		~MenuWindow();

		Menu* getMenu() { return m_menu; }
		void setMenu( Menu* menu ) { m_menu = menu; repaint(); }

		void repaint();

	protected:
		Menu* m_menu;
};

}

#endif // MENUWINDOW_H
