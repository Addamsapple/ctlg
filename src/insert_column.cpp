#include "insert_column.h"
#include "interface.h"
#include "navigate.h"

bool InsertColumn::_execute(StringVector arguments) {
	_position = startingItemColumn + selectedItemColumn;
	catalogue.insertColumn(std::move(arguments[0]), _position);
	return true;
}

void InsertColumn::undo() {
	catalogue.deleteColumn(_position);
}

void InsertColumn::redo() {

}
