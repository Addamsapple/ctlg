#include "delete_item.h"
#include "interface.h"//should probably move catalogue global variable somewhere else
#include "catalogue.h"
#include "navigate.h"
#include "return.h"

//handle #dd, e.g. 22dd to execute dd 22 times, but group together so that undo/redo executes all

bool DeleteItem::execute(StringVector arguments) {
	_position = itemView.firstElement() + itemView.selectedElement();
	if (_position < catalogue.items() && returnCode() == 0) {
		_item = std::move(catalogue[_position]);
		catalogue.deleteItem(_position);
		return true;
	}
	return false;
}

void DeleteItem::undo() {
	catalogue.insertItem(std::move(_item), _position);
	//moveToItem(_position);
}

void DeleteItem::redo() {
	_item = std::move(catalogue[_position]);
	catalogue.deleteItem(_position);
}
