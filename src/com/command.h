#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>

class Command {
	public:
		virtual ~Command() = default;

		virtual bool execute() = 0;
		virtual void undo() {}
		virtual void redo() {}

		virtual bool undoable() { return false; }
};

class UndoableCommand : public Command {
	public:
		virtual bool execute() override = 0;
		virtual void undo() override = 0;
		virtual void redo() override = 0;

		virtual bool undoable() override { return true; }
};

//TODO: allow for different constructors
#define COMMAND(command, ...)\
	class command : public Command {\
		protected:\
			__VA_ARGS__\
		public:\
			command(std::string &&modifier, std::string &&arguments);\
			virtual bool execute() override;\
	}\

#define UNDOABLE_COMMAND(command, ...)\
	class command : public UndoableCommand {\
		protected:\
			__VA_ARGS__\
		public:\
			command(std::string &&modifier, std::string &&arguments);\
			virtual bool execute() override;\
			virtual void undo() override;\
			virtual void redo() override;\
	}\

#endif
