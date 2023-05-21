#include "command_proc.h"
#include "delete_item.h"//testing
#include "insert_item.h"//testing
#include "insert_column.h"
#include "delete_column.h"
#include "set_field.h"

#include "navigation_commands.h"
#include "commands.h"

#include "read.h"
#include "write.h"
#include "sort.h"

//encapsulate in smart pointers, or actually handle deallocations, memory leaks will persist until then.
//WARNING: pass by value at the moment
template<typename T>
std::unique_ptr<Command> commandConstructor(std::string modifier, std::string arguments) {
	//return new T(modifier, arguments);
	return std::make_unique<T>(modifier, arguments);
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

	ADD_INC_RULE(":", ProcessImmediateCommand);
	/*ADD_INC_RULE(ProcessImmediateCommand, ':');
	ADD_INC_RULE(MoveToFirstColumn, '0');
	ADD_INC_RULE(MoveToLastColumn, '$');
	ADD_INC_RULE(MoveToColumn, NUM_TOKEN, '|');
	ADD_INC_RULE(ViewField, 'v');*/
}

#define ADD_IMM_RULE(string, command)\
	immediateProcessor.add(string, commandConstructor<command>)

//command string should include trailing space if arguments are optional: corresponding command should rather handle leading whitespace itself
void loadImmediateCommands() {
	ADD_IMM_RULE("e", Read);
	ADD_IMM_RULE("w", Write);
	ADD_IMM_RULE("q", Quit);
	ADD_IMM_RULE("ic", InsertColumn);
	ADD_IMM_RULE("s", Sort);
	ADD_IMM_RULE("fs", SetField);
}

void loadCommands() {
	loadIncrementalCommands();
	loadImmediateCommands();
}

void runCommand(std::string string) {
	auto matchResult = immediateProcessor.match(string);
	if (matchResult.first) {
		matchResult.first->execute();
	}
}

void runCommand(char character) {
	auto matchResult = incrementalProcessor.match(character);
	if (matchResult.first) {
		matchResult.first->execute();
	}
}
