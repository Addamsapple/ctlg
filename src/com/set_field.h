#include "command.h"

class SetField : public UndoableCommand {
	public:
		virtual bool execute(StringVector arguments) override;
		virtual void undo() override;
		virtual void redo() override;
};
