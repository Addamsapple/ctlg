#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>

using StringVector = std::vector<std::string>;

class Command {
	public:
		//should this not take a reference to a string vector instead?
		virtual void execute(StringVector arguments) = 0;
};

//make subclass that accepts  function callback for simple commands, then dont need to create a new class for each commnad, just the 
#define B_COMMAND(command)\
	class command : public Command {\
		virtual void execute(StringVector arguments) override;\
	};

class UndoableCommand : public Command {
	private:
		virtual bool _execute(StringVector arguments) = 0;
	public:
		virtual void execute(StringVector arguments) override;
		
		virtual void undo() = 0;
		virtual void redo() = 0;
};

#define OVERRIDE_UNDOABLE_MEMBER_FUNCTIONS\
	private:\
		virtual bool _execute(StringVector arguments) override;\
	public:\
		virtual void undo() override;\
		virtual void redo() override;

#endif
