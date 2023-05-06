#include "catalogue.h"

class UndoableTable : public Catalogue {
	protected:
		std::vector<std::unique_ptr<Action>> _undoableActions;
		std::vector<std::unique_ptr<Action>> _redoableActions;

		void _record(std::unique_ptr<Action> &&action);
	public:
		void insertItem(const std::string &string, const size_t position, const bool ignoreErrors);
		void deleteItem(const size_t item);

		void insertColumn(std::vector<std::string> &&fields, const size_t position);
		void deleteColumn(const size_t position);

		void setTitle(std::string &&title, const size_t position);

		void undo();
		void redo();
};
