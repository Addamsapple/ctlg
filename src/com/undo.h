#ifndef UNDO_H
#define UNDO_H

#include "command.h"

void recordCommand(UndoableCommand *command);

void undoCommand();
void redoCommand();

#endif
