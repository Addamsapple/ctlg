#include "command.h"
#include "undo.h"

void UndoableCommand::execute(StringVector arguments) {
	if (_execute(arguments))
		recordCommand(std::move(this));
}
