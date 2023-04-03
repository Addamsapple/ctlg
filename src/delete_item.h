#include "item.h"
#include "command.h"

class DeleteItem : public UndoableCommand {
	private:
		Item _item;
		int _position;

	OVERRIDE_UNDOABLE_MEMBER_FUNCTIONS
};
