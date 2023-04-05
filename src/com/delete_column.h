#include <memory>

#include "command.h"
#include "field.h"

class DeleteColumn : public UndoableCommand {
	private:
		size_t _position;
		std::unique_ptr<Field> _type;
		std::unique_ptr<Field> _title;
		std::vector<std::unique_ptr<Field>> _fields;

		void _claimFields();

	OVERRIDE_UNDOABLE_MEMBER_FUNCTIONS
};
