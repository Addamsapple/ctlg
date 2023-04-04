#include "command.h"
#include "field.h"
#include <memory>

class InsertColumn : public UndoableCommand {
	private:
		size_t _position;
		std::unique_ptr<Field> _type;
		std::unique_ptr<Field> _title;

	OVERRIDE_UNDOABLE_MEMBER_FUNCTIONS
};
