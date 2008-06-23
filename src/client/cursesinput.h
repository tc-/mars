#ifndef CURSESINPUT_H
#define CURSESINPUT_H

namespace cursesclient
{

enum inputCommand {
	cmdNone = 0,
	cmdQuit = 1
};


class CursesInput
{
	public:
		CursesInput();
		~CursesInput();

		inputCommand getInputCommand();
	protected:
	private:
};

}

#endif // CURSESINPUT_H
