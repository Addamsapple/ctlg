#include "set_field.h"

#include "interface.h"
#include "populate.h"
#include "number.h"

SetField::SetField(std::string &&modifier, std::string &&args) : _fields(1), _field(std::move(args)) {
	if (modifier.size() > 0)
		_fields = Number<size_t>::strton(modifier);
}
bool SetField::execute() {
	size_t column = itemColumnView.firstElement() + itemColumnView.selectedElement();
	size_t item = itemView.firstElement() + itemView.selectedElement();
	_fields = std::min(_fields, table.items() - item);
	for (size_t field = 0; field < _fields; field++)
		table.setField(std::string(_field), item + field, column);
	return true;
}

void SetField::undo() {
	for (size_t field = 0; field < _fields; field++)
		table.undo();
}

void SetField::redo() {
	for (size_t field = 0; field < _fields; field++)
		table.redo();
}
