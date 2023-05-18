#ifndef COMMANDS_H
#define COMMANDS_H

#include "command.h"

//consider including Command/variation in name of each command class


COMMAND(ProcessImmediateCommand);
COMMAND(ViewField);

COMMAND(WriteFile);

COMMAND(Quit);

COMMAND(Undo);
COMMAND(Redo);

#endif
