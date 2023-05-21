#ifndef UNDO_H
#define UNDO_H

#include "command.h"

void recordCommand(std::unique_ptr<Command> command);

void undoCommand();
void redoCommand();

#endif
