#include "interface.h"
#include "insert_item.h"
#include "populate.h"
#include "number.h"

InsertItem::InsertItem(std::string &&modifier, std::string &&args) : _items(1){
	if (modifier.size() > 0)
		_items = Number<size_t>::strton(modifier);
}

bool InsertItem::execute() {
	int position = itemView.firstElement() + itemView.selectedElement();
	for (int item = 0; item < _items; item++)
		table.insertItem(repeatField("", table.fields()), position + item, true);
	return true;
}

void InsertItem::undo() {
	for (int item = 0; item < _items; item++)
		table.undo();
}

void InsertItem::redo() {
	for (int item = 0; item < _items; item++)
		table.redo();
}
