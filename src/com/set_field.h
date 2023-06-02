#include "command.h"

UNDOABLE_COMMAND(
	SetField,
		size_t _fields;
		std::string _field;
);
