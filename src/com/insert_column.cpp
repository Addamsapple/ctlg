#include "insert_column.h"
#include "interface.h"
#include "populate.h"
#include "return.h"

bool InsertColumn::execute(StringVector arguments) {
	_position = itemColumnView.firstElement() + itemColumnView.selectedElement();
	std::vector<std::string> fields;
	fields.push_back(std::move(arguments[0]));
	fields.push_back(std::string());
	fields.insert(fields.end(), catalogue.items(), std::string());
	catalogue.insertColumn(std::move(fields), _position);
	return returnCode() == 0;
}

void InsertColumn::undo() {
	catalogue.undo();
	//_action = catalogue.process(std::move(*_action));
}

void InsertColumn::redo() {
	catalogue.redo();
	//_action = catalogue.process(std::move(*_action));
}
