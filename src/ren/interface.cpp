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
		Read read("", command);
		read.execute();
		Command *command;
		//if (incrementalProcessor.match("s2", &command) == FULL_MATCH)
		//incrementalProcessor.match("100j", &command);
			//command->execute();


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
			} else {
				auto matchResult = incrementalProcessor.match(character);
				if (matchResult.first)
					matchResult.first->execute();
					//if ((incrementalProcessor.match(character, &command)) == FULL_MATCH_)
					//command->execute();
			}
			populateScreen();
			doupdate();
		}
	} catch (const std::runtime_error &error) {
		terminate();
		std::cout << error.what() << std::endl;
	}
}
