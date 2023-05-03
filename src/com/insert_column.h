#include "command.h"
#include "field.h"
#include <memory>

#include "actions.h"

class InsertColumn : public UndoableCommand {
	private:
		std::unique_ptr<Action> _action;

		size_t _position;

	OVERRIDE_UNDOABLE_MEMBER_FUNCTIONS
};
