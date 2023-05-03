#include "item.h"
#include "command.h"


//class Action;
#include "actions.h"

class DeleteItem : public UndoableCommand {
	private:
		std::unique_ptr<Action> _action;

		int _position;

	OVERRIDE_UNDOABLE_MEMBER_FUNCTIONS
};
