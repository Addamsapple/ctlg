#include "delete_item.h"
#include "interface.h"//should probably move table global variable somewhere else
#include "populate.h"
#include "return.h"

#include "number.h"

DeleteItem::DeleteItem(std::string &&modifier, std::string &&args) : _items(1) {
	if (modifier.size() > 0)
		_items = Number<size_t>::strton(modifier);
}

bool DeleteItem::execute() {
	setReturnCode(0);
	size_t position = itemView.firstElement() + itemView.selectedElement();
	_items = std::min(_items, table.items() - position);
	for (size_t item = 0; item < _items; item++)
		table.deleteItem(position + _items - 1 - item);
	return true;
}

void DeleteItem::undo() {
	for (size_t item = 0; item < _items; item++)
		table.undo();
}

void DeleteItem::redo() {
	for (size_t item = 0; item < _items; item++)
		table.redo();
}
