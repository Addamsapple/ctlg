#include "insert_column.h"
#include "interface.h"
#include "populate.h"
#include "return.h"

bool InsertColumn::execute(StringVector arguments) {
	_position = itemColumnView.firstElement() + itemColumnView.selectedElement();
	catalogue.insertColumn(std::make_unique<Field>(std::move(arguments[0])), std::make_unique<Field>(""), _position);
	return returnCode() == 0;
}

void InsertColumn::undo() {
	_type = std::move(catalogue.types()[_position]);
	_title = std::move(catalogue.titles()[_position]);
	catalogue.deleteColumn(_position);
}

void InsertColumn::redo() {
	catalogue.insertColumn(std::move(_type), std::move(_title), _position);
}
