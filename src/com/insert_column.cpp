#include "insert_column.h"
#include "interface.h"
#include "populate.h"
#include "return.h"
#include "number.h"

InsertColumn::InsertColumn(std::string &&modifier, std::string &&args) : _columns(1), _type(std::move(args)) {
	if (modifier.size() > 0)
		_columns = Number<size_t>::strton(modifier);
}

//TODO: check result of (first) operation if non-empty type is supplied
bool InsertColumn::execute() {
	size_t position = itemColumnView.firstElement() + itemColumnView.selectedElement();
	for (size_t column = 0; column < _columns; column++) {
		std::vector<std::string> fields;
		fields.push_back(_type);//can't move type because reused
		fields.push_back(std::string());
		fields.insert(fields.end(), table.items(), std::string());
		table.insertColumn(std::move(fields), position + column);
	}
	return returnCode() == 0;
}

void InsertColumn::undo() {
	for (size_t column = 0; column < _columns; column++)
		table.undo();
}

void InsertColumn::redo() {
	for (size_t column = 0; column < _columns; column++)
		table.redo();
}
