#include "navigation_commands.h"

#include "populate.h"
#include "number.h"

MoveUp::MoveUp(std::vector<std::string> args) : _amount(1) { if (args.size() > 0) _amount = Number<size_t>::strton(args[0]); }
bool MoveUp::execute() { itemView.moveBackward(_amount); return true; }

MoveDown::MoveDown(std::vector<std::string> args) : _amount(1) { if (args.size() > 0) _amount = Number<size_t>::strton(args[0]); }
bool MoveDown::execute() { itemView.moveForward(_amount); return true; }

MoveLeft::MoveLeft(std::vector<std::string> args) : _amount(1) { if (args.size() > 0) _amount = Number<size_t>::strton(args[0]); }
bool MoveLeft::execute() { itemColumnView.moveBackward(_amount); return true; }

MoveRight::MoveRight(std::vector<std::string> args) : _amount(1) { if (args.size() > 0) _amount = Number<size_t>::strton(args[0]); }
bool MoveRight::execute() { itemColumnView.moveForward(_amount); return true; }

ScrollUp::ScrollUp(std::vector<std::string> args) : _amount(1) { if (args.size() > 0) _amount = Number<size_t>::strton(args[0]); }
bool ScrollUp::execute() { itemView.scrollBackward(_amount); return true; }

ScrollDown::ScrollDown(std::vector<std::string> args) : _amount(1) { if (args.size() > 0) _amount = Number<size_t>::strton(args[0]); }
bool ScrollDown::execute() { itemView.scrollForward(_amount); return true; }

ScrollLeft::ScrollLeft(std::vector<std::string> args) : _amount(1) { if (args.size() > 0) _amount = Number<size_t>::strton(args[0]); }
bool ScrollLeft::execute() { itemColumnView.scrollBackward(_amount); return true; }

ScrollRight::ScrollRight(std::vector<std::string> args) : _amount(1) { if (args.size() > 0) _amount = Number<size_t>::strton(args[0]); }
bool ScrollRight::execute() { itemColumnView.scrollForward(_amount); return true; }

MoveToFirstItem::MoveToFirstItem(std::vector<std::string>) {}
bool MoveToFirstItem::execute() {
	itemView.selectElement(0);
	return true;
}

MoveToLastItem::MoveToLastItem(std::vector<std::string>) {}
bool MoveToLastItem::execute() {
	itemView.selectElement(itemView.totalElements() - 1);
	return true;
}

MoveToItem::MoveToItem(std::vector<std::string> args) : _item(Number<size_t>::strton(args[0])) {}
bool MoveToItem::execute() {
	itemView.selectElement(_item);
	return true;
}

MoveToFirstColumn::MoveToFirstColumn(std::vector<std::string>) {}
bool MoveToFirstColumn::execute() {
	itemColumnView.selectElement(0);
}

MoveToLastColumn::MoveToLastColumn(std::vector<std::string>) {}
bool MoveToLastColumn::execute() {
	itemColumnView.selectElement(itemColumnView.totalElements() - 1);
	return true;
}

MoveToColumn::MoveToColumn(std::vector<std::string> args) : _column(Number<size_t>::strton(args[0])) {}
bool MoveToColumn::execute() {
	itemColumnView.selectElement(_column);
	return true;
}
