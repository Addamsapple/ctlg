#include "navigation_commands.h"

#include "populate.h"
#include "number.h"

MoveUp::MoveUp(std::string args) : _amount(1) { if (args.size() > 0) _amount = Number<size_t>::strton(args); }
bool MoveUp::execute() { itemView.moveBackward(_amount); return true; }

MoveDown::MoveDown(std::string args) : _amount(1) { if (args.size() > 0) _amount = Number<size_t>::strton(args); }
bool MoveDown::execute() { itemView.moveForward(_amount); return true; }

MoveLeft::MoveLeft(std::string args) : _amount(1) { if (args.size() > 0) _amount = Number<size_t>::strton(args); }
bool MoveLeft::execute() { itemColumnView.moveBackward(_amount); return true; }

MoveRight::MoveRight(std::string args) : _amount(1) { if (args.size() > 0) _amount = Number<size_t>::strton(args); }
bool MoveRight::execute() { itemColumnView.moveForward(_amount); return true; }

ScrollUp::ScrollUp(std::string args) : _amount(1) { if (args.size() > 0) _amount = Number<size_t>::strton(args); }
bool ScrollUp::execute() { itemView.scrollBackward(_amount); return true; }

ScrollDown::ScrollDown(std::string args) : _amount(1) { if (args.size() > 0) _amount = Number<size_t>::strton(args); }
bool ScrollDown::execute() { itemView.scrollForward(_amount); return true; }

ScrollLeft::ScrollLeft(std::string args) : _amount(1) { if (args.size() > 0) _amount = Number<size_t>::strton(args); }
bool ScrollLeft::execute() { itemColumnView.scrollBackward(_amount); return true; }

ScrollRight::ScrollRight(std::string args) : _amount(1) { if (args.size() > 0) _amount = Number<size_t>::strton(args); }
bool ScrollRight::execute() { itemColumnView.scrollForward(_amount); return true; }

MoveToFirstItem::MoveToFirstItem(std::string args) {}
bool MoveToFirstItem::execute() {
	itemView.selectElement(0);
	return true;
}

MoveToLastItem::MoveToLastItem(std::string) {}
bool MoveToLastItem::execute() {
	itemView.selectElement(itemView.totalElements() - 1);
	return true;
}

MoveToItem::MoveToItem(std::string args) : _item(Number<size_t>::strton(args)) {}
bool MoveToItem::execute() {
	itemView.selectElement(_item);
	return true;
}

MoveToFirstColumn::MoveToFirstColumn(std::string) {}
bool MoveToFirstColumn::execute() {
	itemColumnView.selectElement(0);
}

MoveToLastColumn::MoveToLastColumn(std::string) {}
bool MoveToLastColumn::execute() {
	itemColumnView.selectElement(itemColumnView.totalElements() - 1);
	return true;
}

MoveToColumn::MoveToColumn(std::string args) : _column(Number<size_t>::strton(args)) {}
bool MoveToColumn::execute() {
	itemColumnView.selectElement(_column);
	return true;
}
