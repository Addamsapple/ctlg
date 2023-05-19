#include <iostream>

#include "io.h"
#include "command_proc.h"
#include "populate.h"
#include "render.h"
#include "type_proc.h"
#include "read.h"

void run(const std::string &command) {
	loadCommands();
	loadTypes();
	try {
		initialize();
		Read read(command);
		read.execute();
		Command *command;
		//if (immediateProcessor.match("s2", &command) == FULL_MATCH)
		immediateProcessor.match("s2", &command);
			command->execute();


		//immediateProcessor.match(command);
		//auto command = LoadCommand(
		populateScreen();
		doupdate();
		int character;
		while ((character = wgetch(ioWindow))) {
			if (character == KEY_RESIZE) {
				resize();
				itemView.refresh();
				itemColumnView.refresh();
				ioView.refresh();
			}// else
				//incrementalProcessor.match(character);
			populateScreen();
			doupdate();
		}
	} catch (const std::runtime_error &error) {
		terminate();
		std::cout << error.what() << std::endl;
	}
}
