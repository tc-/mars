#ifndef CURSESSCREEN_H
#define CURSESSCREEN_H

namespace cursesclient
{

class CursesWindow;

class CursesScreen
{
	public:
		CursesScreen();
		~CursesScreen();

		CursesWindow* getEast();
		void setEast(CursesWindow* win);
		CursesWindow* getSouth();
		void setSouth(CursesWindow* win);
		CursesWindow* getCenter();
		void setCenter(CursesWindow* win);

		void repaint();

	protected:

		CursesWindow* m_east;
		CursesWindow* m_south;
		CursesWindow* m_center;

		void reorder();

};

}

#endif // CURSESSCREEN_H
