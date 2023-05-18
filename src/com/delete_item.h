#include "item.h"
#include "command.h"


//class Action;
#include "table_actions.h"

UNDOABLE_COMMAND(
	DeleteItem,
		int _position;
);
