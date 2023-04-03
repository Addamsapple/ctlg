#include "command.h"

class EditField : public UndoableCommand {
	private:
		//think of better member names???
		size_t _item;
		size_t _position;
		//std::unique_ptr<Field> field;
		std::string _string;//temporary, use until copy functionality developed

	OVERRIDE_UNDOABLE_MEMBER_FUNCTIONS
};
