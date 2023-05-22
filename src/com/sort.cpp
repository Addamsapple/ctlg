#include "sort.h"

#include <sstream>

#include "number.h"
#include "interface.h"

Sort::Sort(std::string &&modifier, std::string &&args) {
	std::istringstream stream(std::move(args));
	size_t column;
	while (stream >> column)
		if (column < table.fields())
			_columns.push_back(column);
	//NOTE: if columns supplied in args, but all are invalid, will use default order as below
	if (_columns.size() == 0) {
		_columns.reserve(table.fields());
		while (_columns.size() < table.fields())
			_columns.push_back(_columns.size());
	}
}

bool Sort::execute() {
	table.sortItems(std::move(_columns));
	return true;
}

void Sort::undo() {
	table.undo();
}

void Sort::redo() {
	table.redo();
}
