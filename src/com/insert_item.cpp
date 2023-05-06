#include "interface.h"
#include "insert_item.h"
#include "populate.h"
#include "number.h"

//need to extend token/matcher functionality to accomodate variadic string lists, for items that may have an arbitrary number of fields

#include <iostream>

bool InsertItem::execute(StringVector arguments) {
	if (arguments.size() == 1) {
		_position = Number<size_t>::strton(arguments[0]);
		if (returnCode() != 0)
			return false;
	} else
		_position = itemView.firstElement() + itemView.selectedElement();
	catalogue.insertItem(repeatField("", catalogue.fields()), _position, true);
	return true;
}

void InsertItem::undo() {
	catalogue.undo();
}

void InsertItem::redo() {
	catalogue.redo();
}
