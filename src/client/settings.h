#ifndef SETTINGS_H
#define SETTINGS_H

namespace client
{

class Settings
{
	public:

		Settings();
		bool curses_use_colors;

		void load();

	protected:

	private:

};

Settings& sett();

}

#endif // SETTINGS_H
