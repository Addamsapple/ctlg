#include "command.h"

UNDOABLE_COMMAND(
	InsertColumn,
		size_t _columns;
		std::string _type;
);
