#include "delete_item.h"
#include "interface.h"//should probably move table global variable somewhere else
#include "table.h"
#include "populate.h"
#include "return.h"

//handle #dd, e.g. 22dd to execute dd 22 times, but group together so that undo/redo executes all
DeleteItem::DeleteItem(std::string modifier, std::string args) : _position(itemView.firstElement() + itemView.selectedElement()) {}
bool DeleteItem::execute() {
	//_position = itemView.firstElement() + itemView.selectedElement();
	if (_position < table.items() && returnCode() == 0) {
		table.deleteItem(_position);
		return true;
	}
	return false;
}

void DeleteItem::undo() {
	table.undo();
}

void DeleteItem::redo() {
	table.redo();
}
