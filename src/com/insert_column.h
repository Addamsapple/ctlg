#include "command.h"
#include "field.h"
#include <memory>

#include "table_actions.h"

class InsertColumn : public UndoableCommand {
	private:
		size_t _position;

	OVERRIDE_UNDOABLE_MEMBER_FUNCTIONS
};
