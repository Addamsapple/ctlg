#include "command_proc.h"
#include "delete_item.h"//testing
#include "insert_item.h"//testing
#include "insert_column.h"
#include "delete_column.h"
#include "edit_field.h"
#include "edit_type.h"
#include "set_field.h"

#include "navigation_commands.h"
#include "commands.h"

#include "read.h"
#include "write.h"
#include "sort.h"

//encapsulate in smart pointers, or actually handle deallocations, memory leaks will persist until then.
//WARNING: pass by value at the moment
template<typename T>
Command * commandConstructor(std::string modifier, std::string arguments) {
	return new T(modifier, arguments);
}

#define ADD_INC_RULE(string, command)\
	incrementalProcessor.add(string, commandConstructor<command>)

#define ADD_IMM_RULE(string, command)\
	immediateProcessor.add(string, commandConstructor<command>)
void loadIncrementalCommands() {
	ADD_INC_RULE("K", ScrollUp);
	ADD_INC_RULE("J", ScrollDown);
	ADD_INC_RULE("H", ScrollLeft);
	ADD_INC_RULE("L", ScrollRight);
	ADD_INC_RULE("k", MoveUp);
	ADD_INC_RULE("j", MoveDown);
	ADD_INC_RULE("h", MoveLeft);
	ADD_INC_RULE("l", MoveRight);

	ADD_INC_RULE("gg", MoveToFirstItem);
	ADD_INC_RULE("G", MoveToItem);

	ADD_INC_RULE("|", MoveToColumn);
	ADD_INC_RULE("$", MoveToLastColumn);
	
	ADD_INC_RULE("ii", InsertItem);
	ADD_INC_RULE("dd", DeleteItem);
	ADD_INC_RULE("dc", DeleteColumn);
	ADD_INC_RULE("u", Undo);
	ADD_INC_RULE("r", Redo);
	/*ADD_INC_RULE(ProcessImmediateCommand, ':');
	ADD_INC_RULE(MoveToFirstColumn, '0');
	ADD_INC_RULE(MoveToLastColumn, '$');
	ADD_INC_RULE(MoveToColumn, NUM_TOKEN, '|');
	ADD_INC_RULE(ViewField, 'v');
	ADD_INC_RULE(DeleteItem, "dd");
	ADD_INC_RULE(Undo, 'u');
	ADD_INC_RULE(Redo, 'r');
	ADD_INC_RULE(InsertItem, "ii");

	ADD_INC_RULE(DeleteColumn, "dc");

	//ADD_INC_RULE(EditField, "ec");
	//ADD_INC_RULE(EditType, "et");*/

	//incrementalProcessor.reset();
}

//#define ADD_IMM_RULE(command, ...)\
//	immediateProcessor.add(commandConstructor<command>, PatternMatcher(__VA_ARGS__))

#define ADD_IMM_RULE(string, command)\
	immediateProcessor.add(string, commandConstructor<command>)

void loadImmediateCommands() {
	ADD_IMM_RULE("e", Read);
	//ADD_IMM_RULE(Read, "e ", STR_TOKEN);
	//ADD_IMM_RULE(Quit, ":q");

	//ADD_IMM_RULE(InsertColumn, "ic ", STR_TOKEN);
	//ADD_IMM_RULE(Write, "w ", STR_TOKEN);

	ADD_IMM_RULE("s", Sort);
	//ADD_IMM_RULE(Sort, "s", NUM_TOKEN);

	//ADD_IMM_RULE(SetField, "fs ", STR_TOKEN);

	//immediateProcessor.reset();
}

void loadCommands() {
	loadIncrementalCommands();
	loadImmediateCommands();
}
