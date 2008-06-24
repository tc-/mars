
#include <signal.h>
#include <string>

#include "cursesscreen.h"
#include "cursesinput.h"
#include "menuwindow.h"
#include "settings.h"

using namespace cursesclient;
using namespace client;

CursesInput* input = 0;
CursesScreen* screen = 0;

void finalize( int sig )
{
	delete input;
	delete screen;
}

void init()
{
	screen = new CursesScreen();
	input = new CursesInput();

	Menu* m = new Menu();
	m->addItem( "Test", 0 );
	m->addItem( "Menu", 0 );

	screen->setEast( new MenuWindow( m ) );

	signal(SIGINT, finalize);
}

int main( int argc, char* argv[] )
{
	sett().load();
	for ( int i = 0; i < argc; i++ ) {
		if ( std::string(argv[i]) == "--nocolors" ) sett().curses_use_colors = false;
	}

	init();

	bool terminated = false;

	while ( !terminated ) {

		inputCommand c = input->getInputCommand();
		switch ( c ) {
			case cmdQuit: terminated = true; break;
			default: break;
		}

	}

	finalize(0);

	return 0;
}

