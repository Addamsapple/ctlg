#include "interface.h"
#include "insert_item.h"
#include "navigate.h"
#include "number.h"

//need to extend token/matcher functionality to accomodate variadic string lists, for items that may have an arbitrary number of fields

#include <iostream>

bool InsertItem::execute(StringVector arguments) {
	if (arguments.size() == 1) {
		_position = Number<size_t>::strton(arguments[0]);
		if (returnCode() != 0)
			return false;
	} else
		_position = startingItem + selectedItem;
	catalogue.insertItem(repeatField("", catalogue.fields()), _position, true);
	return true;
}

void InsertItem::undo() {
	_item = std::move(catalogue[_position]);
	catalogue.deleteItem(_position);
}

void InsertItem::redo() {
	catalogue.insertItem(std::move(_item), _position);
}
