#include "item.h"
#include "command.h"

//thinking about how to handle potential flags etc that are passsed to some commands
//in the case of append/vs insert: these commands can bind to the same class and perhaps use a different value to construct the class, which means that:
//the class is not duplicated
//minimal state needs to be tracked to accomodate both versions (just a bool/number
//the class does not need complex input processing logic to determine if a flag is passed, and does not need to correspond to a complex pattern (just two pattersns "i" and "a", for example)
//

class InsertItem : public UndoableCommand {
	private:
		int _position;

	OVERRIDE_UNDOABLE_MEMBER_FUNCTIONS
};
