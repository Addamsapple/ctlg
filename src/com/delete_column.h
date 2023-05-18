#include <memory>

#include "command.h"
#include "field.h"

#include "table_actions.h"

UNDOABLE_COMMAND(
	DeleteColumn,
		size_t _position;
);
