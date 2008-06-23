#include "settings.h"

namespace client
{

Settings::Settings()
{
	curses_use_colors = true;
}


void Settings::load()
{

}

Settings* settings_instance = 0;

Settings& sett()
{
	if ( settings_instance == 0) settings_instance = new Settings();
	return *settings_instance;
}

}
