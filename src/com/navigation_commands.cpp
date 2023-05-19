#include "navigation_commands.h"

#include "populate.h"
#include "number.h"

//use macro to prevent code duplication in constructors
//if modifier exists try to convert,
//if conversion does not yield 0 (in which case it probably means overflow, unless "0" is allowed as a modifier, keeps things simple, and then no need to define "0" as command

MoveUp::MoveUp(std::string modifier, std::string args) : _amount(1) {
	if (modifier.size() > 0)
		_amount = Number<size_t>::strton(modifier);
}

bool MoveUp::execute() { itemView.moveBackward(_amount); return true; }

MoveDown::MoveDown(std::string modifier, std::string args) : _amount(1) { if (modifier.size() > 0) _amount = Number<size_t>::strton(modifier); }
bool MoveDown::execute() { itemView.moveForward(_amount); return true; }

MoveLeft::MoveLeft(std::string modifier, std::string args) : _amount(1) { if (modifier.size() > 0) _amount = Number<size_t>::strton(modifier); }
bool MoveLeft::execute() { itemColumnView.moveBackward(_amount); return true; }

MoveRight::MoveRight(std::string modifier, std::string args) : _amount(1) { if (modifier.size() > 0) _amount = Number<size_t>::strton(modifier); }
bool MoveRight::execute() { itemColumnView.moveForward(_amount); return true; }

ScrollUp::ScrollUp(std::string modifier, std::string args) : _amount(1) { if (modifier.size() > 0) _amount = Number<size_t>::strton(modifier); }
bool ScrollUp::execute() { itemView.scrollBackward(_amount); return true; }

ScrollDown::ScrollDown(std::string modifier, std::string args) : _amount(1) { if (modifier.size() > 0) _amount = Number<size_t>::strton(modifier); }
bool ScrollDown::execute() { itemView.scrollForward(_amount); return true; }

ScrollLeft::ScrollLeft(std::string modifier, std::string args) : _amount(1) { if (modifier.size() > 0) _amount = Number<size_t>::strton(modifier); }
bool ScrollLeft::execute() { itemColumnView.scrollBackward(_amount); return true; }

ScrollRight::ScrollRight(std::string modifier, std::string args) : _amount(1) { if (modifier.size() > 0) _amount = Number<size_t>::strton(modifier); }
bool ScrollRight::execute() { itemColumnView.scrollForward(_amount); return true; }

MoveToFirstItem::MoveToFirstItem(std::string modifier, std::string args) {}
bool MoveToFirstItem::execute() {
	itemView.selectElement(0);
	return true;
}

MoveToLastItem::MoveToLastItem(std::string modifier, std::string) {}
bool MoveToLastItem::execute() {
	itemView.selectElement(itemView.totalElements() - 1);
	return true;
}

MoveToItem::MoveToItem(std::string modifier, std::string args) : _item(itemView.totalElements() - 1) { if (modifier.size() > 0) _item = Number<size_t>::strton(modifier); }
bool MoveToItem::execute() {
	itemView.selectElement(_item);
	return true;
}

MoveToFirstColumn::MoveToFirstColumn(std::string modifier, std::string) {}
bool MoveToFirstColumn::execute() {
	itemColumnView.selectElement(0);
	return true;
}

MoveToLastColumn::MoveToLastColumn(std::string modifier, std::string) {}
bool MoveToLastColumn::execute() {
	itemColumnView.selectElement(itemColumnView.totalElements() - 1);
	return true;
}

MoveToColumn::MoveToColumn(std::string modifier, std::string args) : _column(Number<size_t>::strton(args)) {}
bool MoveToColumn::execute() {
	itemColumnView.selectElement(_column);
	return true;
}
