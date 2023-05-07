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

bool ProcessImmediateCommand::execute(StringVector arguments) {
	setIOColourPair(NORMAL_IO);
	setOutput(":");
	if (getInput()) {
		std::string command = std::string(&ioString[0]);
		setOutput("");
		//should redefine to accept pointer to command, and then can execute here instead of inside the processor class?
		//beter for memory handling or not?
		immediateProcessor.match(command);
	}
	return true;
}

//change choice of string to int conversion function

bool ScrollUp::execute(StringVector arguments) {
	int items = 1;
	if (arguments.size() == 1)
		items = stoi(arguments[0]);
	itemView.scrollBackward(items);
	return true;
}

bool ScrollDown::execute(StringVector arguments) {
	int items = 1;
	if (arguments.size() == 1)
		items = stoi(arguments[0]);
	itemView.scrollForward(items);
	return true;
}

bool ScrollLeft::execute(StringVector arguments) {
	int columns = 1;
	if (arguments.size() == 1)
		columns = stoi(arguments[0]);
	itemColumnView.scrollBackward(columns);
	return true;
}

bool ScrollRight::execute(StringVector arguments) {
	int columns = 1;
	if (arguments.size() == 1)
		columns = stoi(arguments[0]);
	itemColumnView.scrollForward(columns);
	return true;
}

bool MoveUp::execute(StringVector arguments) {
	int items = 1;
	if (arguments.size() == 1)
		items = stoi(arguments[0]);
	itemView.moveBackward(items);
	return true;
}

bool MoveDown::execute(StringVector arguments) {
	int items = 1;
	if (arguments.size() == 1)
		items = stoi(arguments[0]);
	itemView.moveForward(items);
	return true;
}

bool MoveLeft::execute(StringVector arguments) {
	int columns = 1;
	if (arguments.size() == 1)
		columns = stoi(arguments[0]);
	itemColumnView.moveBackward(columns);
	return true;
}

bool MoveRight::execute(StringVector arguments) {
	int columns = 1;
	if (arguments.size() == 1)
		columns = stoi(arguments[0]);
	itemColumnView.moveForward(columns);
	return true;
}

bool GoToFirstItem::execute(StringVector arguments) {
	itemView.selectElement(0);
	return true;
}

bool GoToLastItem::execute(StringVector arguments) {
	itemView.selectElement(table.items() - 1);
	return true;
}

bool GoToItem::execute(StringVector arguments) {
	int item = stoi(arguments[0]);
	itemView.selectElement(item);
	return true;
}

bool GoToFirstItemColumn::execute(StringVector arguments) {
	itemColumnView.selectElement(0);
	return true;
}

bool GoToLastItemColumn::execute(StringVector arguments) {
	itemColumnView.selectElement(table.fields() - 1);
	return true;
}

bool GoToItemColumn::execute(StringVector arguments) {
	int column = stoi(arguments[0]);
	itemColumnView.selectElement(column);
	return true;
}

bool ViewField::execute(StringVector arguments) {
	setOutput(table[itemView.firstElement() + itemView.selectedElement()].get(itemColumnView.firstElement() + itemColumnView.selectedElement()).string());
	return true;
}

//rather modify some global variable, so that program termination is easier to follow
bool Quit::execute(StringVector arguments) {
	terminate();
	exit(0);
	return true;
}

#include "commands.h"

bool Undo::execute(StringVector arguments) {
	undoCommand();
	return true;
}

bool Redo::execute(StringVector arguments) {
	redoCommand();
	return true;
}
