#include <memory>

#include "command.h"

std::vector<std::unique_ptr<UndoableCommand>> commandHistory;

size_t undoableCommands;

void recordCommand(UndoableCommand *command) {
	commandHistory.erase(commandHistory.begin() + undoableCommands++, commandHistory.end());
	commandHistory.emplace_back(std::move(command));
}

void undoCommand() {
	if (undoableCommands != 0)
		commandHistory[--undoableCommands]->undo();
}

void redoCommand() {
	if (undoableCommands != commandHistory.size())
		commandHistory[undoableCommands++]->redo();
}
