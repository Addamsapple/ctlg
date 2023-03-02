#include <iostream>//use io instead

#include "io.h"
#include "command_proc.h"
#include "render.h"
#include "resize.h"
#include "type_proc.h"

void run(const std::string &command) {
	loadCommands();
	loadTypes();
	try {
		initialize();
		immediateProcessor.match(command);
		int character;
		while ((character = wgetch(ioWindow))) {
			if (character == KEY_RESIZE) resizeScreen();
			else incrementalProcessor.match(character);
			doupdate();
		}
	} catch (const std::runtime_error &error) {
		terminate();
		std::cout << error.what() << std::endl;
	}
}
