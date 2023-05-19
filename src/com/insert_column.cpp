#include "insert_column.h"
#include "interface.h"
#include "populate.h"
#include "return.h"

InsertColumn::InsertColumn(std::string args) : _type(std::move(args)),  _position(itemColumnView.firstElement() + itemColumnView.selectedElement()) {}
bool InsertColumn::execute() {
	//_position = itemColumnView.firstElement() + itemColumnView.selectedElement();
	std::vector<std::string> fields;
	//fields.push_back(std::move(arguments[0]));
	fields.push_back(std::move(_type));
	fields.push_back(std::string());
	fields.insert(fields.end(), table.items(), std::string());
	table.insertColumn(std::move(fields), _position);
	return returnCode() == 0;
}

void InsertColumn::undo() {
	table.undo();
	//_action = table.process(std::move(*_action));
}

void InsertColumn::redo() {
	table.redo();
	//_action = table.process(std::move(*_action));
}
