#include "delete_column.h"
#include "interface.h"
#include "populate.h"

bool DeleteColumn::execute(StringVector arguments) {
	_position = itemColumnView.firstElement() + itemColumnView.selectedElement();
	table.deleteColumn(_position);
	return true;
}

void DeleteColumn::undo() {
	table.undo();
}

void DeleteColumn::redo() {
	table.redo();
}
