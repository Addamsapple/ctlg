#ifndef TABLE_VIEW_H
#define TABLE_VIEW_H

#include <limits>

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

		template<typename T> void filter(T predicate);

		void clear();

		ItemView types() const;
		ItemView titles() const;

		ItemView operator[](size_t item) const;

		TableViewIterator begin() const;
		TableViewIterator end() const;

		size_t items() const;
		size_t fields() const;

		void undo();
		void redo();
};

template<typename T>
void TableView::filter(T predicate) {
	for (size_t item = _items.size() - 1; item < std::numeric_limits<size_t>::max(); item--)
		if (!predicate((*this)[_items[item]]))
			_items.erase(_items.begin() + item);
}

#endif
