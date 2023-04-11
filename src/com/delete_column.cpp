#include "delete_column.h"
#include "interface.h"
#include "navigate.h"

bool DeleteColumn::execute(StringVector arguments) {
	_position = startingItemColumn + selectedItemColumn;
	_claimFields();
	catalogue.deleteColumn(_position);
	return true;
}

void DeleteColumn::undo() {
	catalogue.insertColumn(std::move(_type), std::move(_title), _fields, _position);
	_fields.clear();
}

void DeleteColumn::redo() {
	_claimFields();
	catalogue.deleteColumn(_position);
}

void DeleteColumn::_claimFields() {
	_type = std::move(catalogue.typeHeader()[_position]);
	_title = std::move(catalogue.titleHeader()[_position]);
	_fields.reserve(catalogue.items());
	for (auto item = catalogue.begin(); item != catalogue.end(); item++)
		_fields.push_back(std::move((*item)[_position]));
}
