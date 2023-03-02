#include "command_proc.h"
#include "interface.h"
#include "io.h"
#include "navigate.h"
#include "render.h"

void Load::execute(StringVector arguments) {
	catalogue.load(arguments[0]);
	load();
}

void ProcessImmediateCommand::execute(StringVector arguments) {
	setOutput(":");
	if (getInput())
		immediateProcessor.match(&ioString[0]);
	setOutput("");
}

//change choice of string to int conversion function

void ScrollUp::execute(StringVector arguments) {
	int items = 1;
	if (arguments.size() == 1)
		items = stoi(arguments[0]);
	scrollUpThroughItems(items);
}

void ScrollDown::execute(StringVector arguments) {
	int items = 1;
	if (arguments.size() == 1)
		items = stoi(arguments[0]);
	scrollDownThroughItems(items);
}

void ScrollLeft::execute(StringVector arguments) {
	int columns = 1;
	if (arguments.size() == 1)
		columns = stoi(arguments[0]);
	scrollLeftThroughItems(columns);
}

void ScrollRight::execute(StringVector arguments) {
	int columns = 1;
	if (arguments.size() == 1)
		columns = stoi(arguments[0]);
	scrollRightThroughItems(columns);
}

void MoveUp::execute(StringVector arguments) {
	int items = 1;
	if (arguments.size() == 1)
		items = stoi(arguments[0]);
	moveUpThroughItems(items);
}


void MoveDown::execute(StringVector arguments) {
	int items = 1;
	if (arguments.size() == 1)
		items = stoi(arguments[0]);
	moveDownThroughItems(items);
}

void MoveLeft::execute(StringVector arguments) {
	int columns = 1;
	if (arguments.size() == 1)
		columns = stoi(arguments[0]);
	moveLeftThroughItems(columns);
}

void MoveRight::execute(StringVector arguments) {
	int columns = 1;
	if (arguments.size() == 1)
		columns = stoi(arguments[0]);
	moveRightThroughItems(columns);
}

void GoToFirstItem::execute(StringVector arguments) {
	moveToItem(0);
}

void GoToLastItem::execute(StringVector arguments) {
	moveToItem(catalogue.items() - 1);
}

void GoToItem::execute(StringVector arguments) {
	moveToItem(stoi(arguments[0]));
}

void GoToFirstItemColumn::execute(StringVector arguments) {
	moveToItemColumn(0);
}

void GoToLastItemColumn::execute(StringVector arguments) {
	moveToItemColumn(catalogue.fields() - 1);
}

void GoToItemColumn::execute(StringVector arguments) {
	moveToItemColumn(stoi(arguments[0]));
}

void ViewField::execute(StringVector arguments) {
	setOutput(catalogue[startingItem + selectedItem][startingItemColumn + selectedItemColumn].string());
}

void Quit::execute(StringVector arguments) {
	terminate();
	exit(0);
}
