#include "command.h"

class InsertColumn : public UndoableCommand {
	private:
		size_t _position;

	OVERRIDE_UNDOABLE_MEMBER_FUNCTIONS
};
