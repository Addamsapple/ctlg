#include <fstream>

#include "table.h"
#include "command_proc.h"
#include "interface.h"
#include "io.h"
#include "populate.h"
#include "number.h"
#include "render.h"
#include "return.h"
#include "type_proc.h"
#include "undo.h"

ProcessImmediateCommand::ProcessImmediateCommand(std::string args) {}
bool ProcessImmediateCommand::execute() {
	setIOColourPair(NORMAL_IO);
	setOutput(":");
	if (getInput()) {
		std::string command = std::string(&ioString[0]);
		setOutput("");
		//should redefine to accept pointer to command, and then can execute here instead of inside the processor class?
		//beter for memory handling or not?
		//immediateProcessor.match(command);
	}
	return true;
}

//change choice of string to int conversion function
ViewField::ViewField(std::string args) {}
bool ViewField::execute() {
	setOutput(table[itemView.firstElement() + itemView.selectedElement()].get(itemColumnView.firstElement() + itemColumnView.selectedElement()).string());
	return true;
}

//rather modify some global variable, so that program termination is easier to follow
Quit::Quit(std::string args) {}
bool Quit::execute() {
	terminate();
	exit(0);
	return true;
}

#include "commands.h"

Undo::Undo(std::string args) {}
bool Undo::execute() {
	undoCommand();
	return true;
}

Redo::Redo(std::string args) {}
bool Redo::execute() {
	redoCommand();
	return true;
}
