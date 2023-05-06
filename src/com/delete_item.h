#include "item.h"
#include "command.h"


//class Action;
#include "actions.h"

class DeleteItem : public UndoableCommand {
	private:
		int _position;

	OVERRIDE_UNDOABLE_MEMBER_FUNCTIONS
};
