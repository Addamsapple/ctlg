#ifndef TABLE_VIEW_H
#define TABLE_VIEW_H

#include "table_actions.h"
#include "table_view_iterator.h"

class TableView {
	private:
		Table _table;

		std::vector<size_t> _items;
		std::vector<size_t> _fields;

		class Action;
		class InsertItemAction;
		class DeleteItemAction;
		class InsertColumnAction;
		class DeleteColumnAction;

		using record_type = std::pair<std::unique_ptr<Action>, bool>;

		std::vector<record_type> _undoableActions;
		std::vector<record_type> _redoableActions;

		void _record(record_type &&action);
	public:
		void insertItem(const std::string &string, const size_t position, const bool ignoreErrors);
		void deleteItem(const size_t item);
		void insertColumn(std::vector<std::string> &&fields, const size_t position);
		void deleteColumn(const size_t position);
		void setField(std::string &&field, size_t item, size_t column);
		void setTitle(std::string &&title, const size_t position);

		void clear();

		ItemView types() const;
		ItemView titles() const;

		//const Item & operator[](size_t item) const;
		const Field & field(size_t row, size_t column) const;

		TableViewIterator begin() const;
		TableViewIterator end() const;

		size_t items() const;
		size_t fields() const;

		void undo();
		void redo();
};

#endif
