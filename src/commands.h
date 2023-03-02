#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include <vector>

using StringVector = std::vector<std::string>;

class Command {
	public:
		virtual void execute(StringVector arguments) = 0;
		virtual void redo() {}
		virtual void undo() {}
};

#define B_COMMAND(command)\
	class command : public Command {\
		virtual void execute(StringVector arguments) override;\
	};

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

B_COMMAND(Load);

B_COMMAND(Quit);

#endif
