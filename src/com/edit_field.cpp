#include "edit_field.h"

#include "navigate.h"
#include "io.h"
#include "interface.h"
#include "render.h"
#include "return.h"

//rename class to EditItemField???
bool EditField::_execute(StringVector arguments) {
	_item = startingItem + selectedItem;
	_position = startingItemColumn + selectedItemColumn;
	setOutput(catalogue[_item][_position]->string());
	while (getInput()) {
		_field = std::unique_ptr<Field>(catalogue.itemConstructor()[_position]->construct(ioString.data()));
		if (returnCode() == 0) {
			catalogue[_item][_position].swap(_field);
			return true;
		}
	}
	return false;
}

void EditField::undo() {
	catalogue[_item][_position].swap(_field);
}

void EditField::redo() {
	catalogue[_item][_position].swap(_field);
}