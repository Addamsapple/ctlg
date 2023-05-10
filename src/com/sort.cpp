#include "sort.h"
#include "number.h"
#include "interface.h"

bool Sort::execute(StringVector arguments) {
	std::vector<size_t> columns;
	columns.push_back(Number<size_t>::strton(arguments[0]));
	table.sortItems(std::move(columns));
	return true;
}

void Sort::undo() {
	table.undo();
}

void Sort::redo() {
	table.redo();
}
