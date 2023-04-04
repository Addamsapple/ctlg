#include "interface.h"
#include "insert_item.h"
#include "navigate.h"

//need to extend token/matcher functionality to accomodate variadic string lists, for items that may have an arbitrary number of fields

#include <iostream>

//temporarily just create empty item
bool InsertItem::_execute(StringVector arguments) {
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
