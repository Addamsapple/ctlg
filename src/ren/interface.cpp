#include <iostream>

#include "io.h"
#include "command_proc.h"
#include "populate.h"
#include "render.h"
#include "type_proc.h"
#include "read.h"

void run(const std::string &command) {
	loadTypes();
	try {
		initialize();
		Read read("", std::string(command));
		read.execute();
		populateScreen();
		doupdate();
		int character;
		while ((character = wgetch(ioWindow))) {
			if (character == KEY_RESIZE) {
				resize();
				itemView.refresh();
				itemColumnView.refresh();
				ioView.refresh();
			} else {
				runCommand(character);
			}
			populateScreen();
			doupdate();
		}
	} catch (const std::runtime_error &error) {
		terminate();
		std::cout << error.what() << std::endl;
	}
}
