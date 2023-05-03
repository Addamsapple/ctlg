#include "delete_column.h"
#include "interface.h"
#include "populate.h"

bool DeleteColumn::execute(StringVector arguments) {
	_position = itemColumnView.firstElement() + itemColumnView.selectedElement();
	_action = catalogue.deleteColumn(_position);
	return true;
}

void DeleteColumn::undo() {
	_action = catalogue.process(std::move(*_action));
}

void DeleteColumn::redo() {
	_action = catalogue.process(std::move(*_action));
}
