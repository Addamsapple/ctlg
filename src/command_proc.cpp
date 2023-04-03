#include "command_proc.h"
#include "delete_item.h"//testing
#include "insert_item.h"//testing

//encapsulate in smart pointers, or actually handle deallocations, memory leaks will persist until then.
template<typename T>
Command * commandConstructor() {
	return new T();
}

#define ADD_INC_RULE(command, ...)\
	incrementalProcessor.add(commandConstructor<command>, PatternMatcher(__VA_ARGS__))

void loadIncrementalCommands() {
	ADD_INC_RULE(ProcessImmediateCommand, ':');
	ADD_INC_RULE(ScrollUp, 'K');
	ADD_INC_RULE(ScrollDown, 'J');
	ADD_INC_RULE(ScrollLeft, 'H');
	ADD_INC_RULE(ScrollRight, 'L');
	ADD_INC_RULE(MoveUp, 'k');
	ADD_INC_RULE(MoveDown, 'j');
	ADD_INC_RULE(MoveLeft, 'h');
	ADD_INC_RULE(MoveRight, 'l');
	ADD_INC_RULE(ScrollUp, NUM_TOKEN, 'K');
	ADD_INC_RULE(ScrollDown, NUM_TOKEN, 'J');
	ADD_INC_RULE(ScrollLeft, NUM_TOKEN, 'H');
	ADD_INC_RULE(ScrollRight, NUM_TOKEN, 'L');
	ADD_INC_RULE(MoveUp, NUM_TOKEN, 'k');
	ADD_INC_RULE(MoveDown, NUM_TOKEN, 'j');
	ADD_INC_RULE(MoveLeft, NUM_TOKEN, 'h');
	ADD_INC_RULE(MoveRight, NUM_TOKEN, 'l');
	ADD_INC_RULE(GoToFirstItem, "gg");
	ADD_INC_RULE(GoToLastItem, 'G');
	ADD_INC_RULE(GoToItem, NUM_TOKEN, 'G');
	ADD_INC_RULE(GoToFirstItemColumn, '0');
	ADD_INC_RULE(GoToLastItemColumn, '$');
	ADD_INC_RULE(GoToItemColumn, NUM_TOKEN, '|');
	ADD_INC_RULE(ViewField, 'v');
	ADD_INC_RULE(DeleteItem, "dd");
	ADD_INC_RULE(Undo, 'u');
	ADD_INC_RULE(Redo, 'r');
	ADD_INC_RULE(InsertItem, "ii");

	incrementalProcessor.reset();
}

#define ADD_IMM_RULE(command, ...)\
	immediateProcessor.add(commandConstructor<command>, PatternMatcher(__VA_ARGS__))

void loadImmediateCommands() {
	ADD_IMM_RULE(Load, "e ", STR_TOKEN);
	ADD_IMM_RULE(Quit, ":q");
	ADD_IMM_RULE(EditType, "rr", NUM_TOKEN);

	immediateProcessor.reset();
}

void loadCommands() {
	loadIncrementalCommands();
	loadImmediateCommands();
}
