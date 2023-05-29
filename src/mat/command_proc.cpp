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

template<typename T>
std::unique_ptr<Command> commandConstructor(std::string &&modifier, std::string &&arguments) {
	return std::make_unique<T>(std::move(modifier), std::move(arguments));
}

#define PAIR(string_, command)\
	std::make_pair(std::string(string_), commandConstructor<command>)

const CharacterCommandMatcher incrementalProcessor(
	PAIR("K", ScrollUp),
	PAIR("J", ScrollDown),
	PAIR("H", ScrollLeft),
	PAIR("L", ScrollRight),
	PAIR("k", MoveUp),
	PAIR("j", MoveDown),
	PAIR("h", MoveLeft),
	PAIR("l", MoveRight),
	PAIR("gg", MoveToFirstItem),
	PAIR("G", MoveToItem),
	PAIR("|", MoveToColumn),
	PAIR("$", MoveToLastColumn),
	PAIR("ii", InsertItem),
	PAIR("dd", DeleteItem),
	PAIR("dc", DeleteColumn),
	PAIR("u", Undo),
	PAIR("r", Redo),
	PAIR(":", ProcessImmediateCommand)
);

const StringCommandMatcher immediateProcessor(
	PAIR("e", Read),
	PAIR("w", Write),
	PAIR("q", Quit),
	PAIR("ic", InsertColumn),
	PAIR("s", Sort),
	PAIR("fs", SetField)
);

#include "undo.h"//TEMP
//TODO: move these functions elsewhere
void runCommand(std::string string) {
	auto matchResult = immediateProcessor.match(string);
	if (matchResult.first) {
		matchResult.first->execute();
		if (matchResult.first->undoable())
			recordCommand(std::move(matchResult.first));
	}
}

void runCommand(char character) {
	auto matchResult = incrementalProcessor.match(character);
	if (matchResult.first) {
		matchResult.first->execute();
		if (matchResult.first->undoable())
			recordCommand(std::move(matchResult.first));
	}
}
