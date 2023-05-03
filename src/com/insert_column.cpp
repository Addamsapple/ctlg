#include "insert_column.h"
#include "interface.h"
#include "populate.h"
#include "return.h"

bool InsertColumn::execute(StringVector arguments) {
	_position = itemColumnView.firstElement() + itemColumnView.selectedElement();
	//make Catalogue::insertColumn work with rvalues?
	std::vector<std::string> fields = std::vector(catalogue.items(), std::string());
	_action = catalogue.insertColumn(std::move(arguments[0]), "", fields, _position);
	return returnCode() == 0;
}

void InsertColumn::undo() {
	_action = catalogue.process(std::move(*_action));
}

void InsertColumn::redo() {
	_action = catalogue.process(std::move(*_action));
}
