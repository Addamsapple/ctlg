#include <memory>

#include "command.h"
#include "field.h"

#include "actions.h"

class DeleteColumn : public UndoableCommand {
	private:
		size_t _position;

	OVERRIDE_UNDOABLE_MEMBER_FUNCTIONS
};
