#ifndef NAVIGATION_COMMANDS_H
#define NAVIGATION_COMMANDS_H

#include "command.h"

COMMAND(MoveUp,
		size_t _amount;);
COMMAND(MoveDown,
		size_t _amount;);
COMMAND(MoveLeft,
		size_t _amount;);
COMMAND(MoveRight,
		size_t _amount;);

COMMAND(ScrollUp,
		size_t _amount;);
COMMAND(ScrollDown,
		size_t _amount;);
COMMAND(ScrollLeft,
		size_t _amount;);
COMMAND(ScrollRight,
		size_t _amount;);

COMMAND(MoveToFirstItem);
COMMAND(MoveToLastItem);
COMMAND(MoveToItem,
		size_t _item;);

COMMAND(MoveToFirstColumn);
COMMAND(MoveToLastColumn);
COMMAND(MoveToColumn,
		size_t _column;);

#endif
