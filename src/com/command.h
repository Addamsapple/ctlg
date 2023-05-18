#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>

class Command {
	public:
		virtual ~Command() = default;
		//should this not take a reference to a string vector instead?
		virtual bool execute() = 0;
		virtual bool undoable();
};

class UndoableCommand : public Command {
	public:
		virtual bool execute() override = 0;
		virtual bool undoable() final override;
		virtual void undo() = 0;
		virtual void redo() = 0;
};

#define COMMAND(command, ...)\
	class command : public Command {\
		protected:\
			__VA_ARGS__\
		public:\
			command(std::vector<std::string> args);\
			virtual bool execute() override;\
	}\

#define UNDOABLE_COMMAND(command, ...)\
	class command : public UndoableCommand {\
		protected:\
			__VA_ARGS__\
		public:\
			command(std::vector<std::string> args);\
			virtual bool execute() override;\
			virtual void undo() override;\
			virtual void redo() override;\
	}\

#endif
