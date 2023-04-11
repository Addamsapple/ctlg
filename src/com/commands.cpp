#include <fstream>

#include "catalogue.h"
#include "command_proc.h"
#include "interface.h"
#include "io.h"
#include "navigate.h"
#include "number.h"
#include "render.h"
#include "return.h"
#include "type_proc.h"
#include "undo.h"

//not clearing properly when new file loaded
void loadTypeHeader(const std::string &item, bool &ignoredItem) {
	auto item_ = splitItem(item);
	catalogue.setTypes<StringVector &>(item_);
	while (returnCode() != 0) {
		displayReturnMessage();
		int character = wgetch(ioWindow);
		if (character == 'a') {
			setOutput(item);
			if (getInput()) {
				item_ = splitItem(ioString.data());
				catalogue.setTypes<StringVector &>(item_);
				ignoredItem = false;
			}
		} else if (character == 'b' || character == 'c') {
			setOutput(std::to_string(item_.size()));
			if (getInput()) {
				size_t fields = Number<size_t>::strton(ioString.data());
				if (returnCode() == 0) {
					catalogue.setTypes<const std::string &>(repeatField("fld", fields));
					ignoredItem = character == 'c';
				}
			}
		}
	}
}

//add ignore error option here aswell, incase titles only defined for first few columns
void loadTitleHeader(const std::string &item) {
	catalogue.setTitles(item);
	while (returnCode() != 0) {
		displayReturnMessage();
		int character = wgetch(ioWindow);
		if (character == 'a') {
			setOutput(item);
			if (getInput())
				catalogue.setTitles(ioString.data());
		} else if (character == 'b')
			catalogue.setTitles(repeatField("", catalogue.fields()));
	}
}

void loadItem(const std::string &item, bool &haltOnError, bool &ignoreErrors) {
	catalogue.appendItem(item, ignoreErrors);
	if (haltOnError)
		while (returnCode() != 0) {
			displayReturnMessage();
			int character = wgetch(ioWindow);
			if (character == 'a') {
				setOutput(item);
				if (getInput())
					catalogue.appendItem(ioString.data(), ignoreErrors);
			} else if (character == 'b') {
				ignoreErrors = true;
			} else if (character == 'c') {
				haltOnError = false;//not working properly
			} else if (character == 'd') {
				setReturnCode(0, "");
			}
		}
}

//ioString is not reset at end of function, so if errors occur, the last one will be in the ioString when the command finishes executing
bool Load::execute(StringVector arguments) {
	bool ignoredTypeHeader = false;//find a more appropriate name
	bool haltOnError = true;
	bool ignoreErrors = false;
	std::ifstream file(arguments[0]);
	std::string item;
	std::getline(file, item);
	loadTypeHeader(item, ignoredTypeHeader);
	if (!ignoredTypeHeader)
		std::getline(file, item);
	loadTitleHeader(item);
	while (std::getline(file, item))
		loadItem(item, haltOnError, ignoreErrors);
	load();
	return true;
}

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
	scrollUpThroughItems(items);
	return true;
}

bool ScrollDown::execute(StringVector arguments) {
	int items = 1;
	if (arguments.size() == 1)
		items = stoi(arguments[0]);
	scrollDownThroughItems(items);
	return true;
}

bool ScrollLeft::execute(StringVector arguments) {
	int columns = 1;
	if (arguments.size() == 1)
		columns = stoi(arguments[0]);
	scrollLeftThroughItems(columns);
	return true;
}

bool ScrollRight::execute(StringVector arguments) {
	int columns = 1;
	if (arguments.size() == 1)
		columns = stoi(arguments[0]);
	scrollRightThroughItems(columns);
	return true;
}

bool MoveUp::execute(StringVector arguments) {
	int items = 1;
	if (arguments.size() == 1)
		items = stoi(arguments[0]);
	moveUpThroughItems(items);
	return true;
}

bool MoveDown::execute(StringVector arguments) {
	int items = 1;
	if (arguments.size() == 1)
		items = stoi(arguments[0]);
	moveDownThroughItems(items);
	return true;
}

bool MoveLeft::execute(StringVector arguments) {
	int columns = 1;
	if (arguments.size() == 1)
		columns = stoi(arguments[0]);
	moveLeftThroughItems(columns);
	return true;
}

bool MoveRight::execute(StringVector arguments) {
	int columns = 1;
	if (arguments.size() == 1)
		columns = stoi(arguments[0]);
	moveRightThroughItems(columns);
	return true;
}

bool GoToFirstItem::execute(StringVector arguments) {
	moveToItem(0);
	return true;
}

bool GoToLastItem::execute(StringVector arguments) {
	moveToItem(catalogue.items() - 1);
	return true;
}

bool GoToItem::execute(StringVector arguments) {
	moveToItem(stoi(arguments[0]));
	return true;
}

bool GoToFirstItemColumn::execute(StringVector arguments) {
	moveToItemColumn(0);
	return true;
}

bool GoToLastItemColumn::execute(StringVector arguments) {
	moveToItemColumn(catalogue.fields() - 1);
	return true;
}

bool GoToItemColumn::execute(StringVector arguments) {
	moveToItemColumn(stoi(arguments[0]));
	return true;
}

bool ViewField::execute(StringVector arguments) {
	setOutput(catalogue[startingItem + selectedItem][startingItemColumn + selectedItemColumn]->string());
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
