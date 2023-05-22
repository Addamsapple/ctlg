#include "delete_column.h"
#include "interface.h"
#include "populate.h"

DeleteColumn::DeleteColumn(std::string &&modifier, std::string &&args) : _position(itemColumnView.firstElement() + itemColumnView.selectedElement()) {}
bool DeleteColumn::execute() {
	//_position = itemColumnView.firstElement() + itemColumnView.selectedElement();
	table.deleteColumn(_position);
	return true;
}

void DeleteColumn::undo() {
	table.undo();
}

void DeleteColumn::redo() {
	table.redo();
}
