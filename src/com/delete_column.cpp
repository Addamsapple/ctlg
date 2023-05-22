#include "delete_column.h"
#include "interface.h"
#include "populate.h"
#include "number.h"

DeleteColumn::DeleteColumn(std::string &&modifier, std::string &&args) : _columns(1) {
	if (modifier.size() > 0)
		_columns = Number<size_t>::strton(modifier);
}

bool DeleteColumn::execute() {
	size_t position = itemColumnView.firstElement() + itemColumnView.selectedElement();
	_columns = std::min(_columns, table.fields() - position);
	for (size_t column = 0; column < _columns; column++)
		table.deleteColumn(position + _columns - 1 - column);
	return true;
}

void DeleteColumn::undo() {
	for (size_t column = 0; column < _columns; column++)
		table.undo();
}

void DeleteColumn::redo() {
	for (size_t column = 0; column < _columns; column++)
		table.redo();
}
