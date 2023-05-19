#include "sort.h"
#include "number.h"
#include "interface.h"

#include <iostream>

Sort::Sort(std::string args) : _column(Number<size_t>::strton(args)) { std::cerr << args << '\n' << _column << '\n'; }
bool Sort::execute() {
	std::vector<size_t> columns;
	//columns.push_back(Number<size_t>::strton(arguments[0]));
	columns.push_back(_column);
	table.sortItems(std::move(columns));
	return true;
}

void Sort::undo() {
	table.undo();
}

void Sort::redo() {
	table.redo();
}
