#include <memory>

#include "command.h"

//consider separating into done/ undone stacks for performance and ease of understanding

std::vector<std::unique_ptr<Command>> commandHistory;

size_t undoableCommands;

void recordCommand(std::unique_ptr<Command> command) {
	commandHistory.erase(commandHistory.begin() + undoableCommands++, commandHistory.end());
	commandHistory.push_back(std::move(command));
}

void undoCommand() {
	if (undoableCommands != 0)
		commandHistory[--undoableCommands]->undo();
}

void redoCommand() {
	if (undoableCommands != commandHistory.size())
		commandHistory[undoableCommands++]->redo();
}
