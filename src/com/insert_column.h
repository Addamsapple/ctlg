#include "command.h"
#include "field.h"
#include <memory>

#include "table_actions.h"

UNDOABLE_COMMAND(
	InsertColumn,
		std::string _type;
		size_t _position;
);

/*
class InsertColumn : public UndoableCommand {
	private:
		size_t _position;

};
*/
