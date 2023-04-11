#include "command.h"
#include "undo.h"

//dont always want to record undoable commands, since would like to be able to embed commands inside each other, and only have the top level command appear in the history.
//e.g append item would reuse insert item command by embedding it, and calling its execute with custom arguments?
