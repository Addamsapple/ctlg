#ifndef COMMANDS_H
#define COMMANDS_H

#include "command.h"

//consider including Command/variation in name of each command class

B_COMMAND(ProcessImmediateCommand);
B_COMMAND(ScrollUp);
B_COMMAND(ScrollDown);
B_COMMAND(ScrollLeft);
B_COMMAND(ScrollRight);
B_COMMAND(MoveUp);
B_COMMAND(MoveDown);
B_COMMAND(MoveLeft);
B_COMMAND(MoveRight);
B_COMMAND(GoToFirstItem);
B_COMMAND(GoToLastItem);
B_COMMAND(GoToItem);
B_COMMAND(GoToFirstItemColumn);
B_COMMAND(GoToLastItemColumn);
B_COMMAND(GoToItemColumn);
B_COMMAND(ViewField);

//rename to LoadCatalogue, LoadFile, ReadFile, ReadCatalogue
B_COMMAND(Load);

B_COMMAND(WriteFile);

B_COMMAND(Quit);

B_COMMAND(Undo);
B_COMMAND(Redo);

#endif
