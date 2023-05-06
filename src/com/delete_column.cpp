#include "delete_column.h"
#include "interface.h"
#include "populate.h"

bool DeleteColumn::execute(StringVector arguments) {
	_position = itemColumnView.firstElement() + itemColumnView.selectedElement();
	catalogue.deleteColumn(_position);
	return true;
}

void DeleteColumn::undo() {
	catalogue.undo();
}

void DeleteColumn::redo() {
	catalogue.redo();
}
