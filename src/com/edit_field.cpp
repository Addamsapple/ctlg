#include "edit_field.h"

#include "navigate.h"
#include "io.h"
#include "interface.h"

//need access to catalogue's _itemConstructor to use the correct reassign method
//or just define a reassignItemField method, etc to access it use it 


//rename class to EditItemField???
bool EditField::_execute(StringVector arguments) {
	_item = startingItem + selectedItem;
	_position = startingItemColumn + selectedItemColumn;
	//check if item/field actually exists
	_string = catalogue[_item][_position]->string();
	setOutput(_string);
	if (getInput()) {
		//need to access reassign in _itemConstructor

	}
	return false;
}

void EditField::undo() {

}

void EditField::redo() {

}
