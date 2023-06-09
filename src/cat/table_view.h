#ifndef TABLE_VIEW_H
#define TABLE_VIEW_H

#include "table_actions.h"
#include "item_view.h"

class TableIterator {
	public:
		//const types???
		using value_type = ItemView;
		using reference = ItemView;
		using pointer = const ItemView *;
		using difference_type = ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;
	private:
		const Table *_table;
		std::vector<size_t>::const_iterator _index;
		const std::vector<size_t> *_indices;
	public:
		TableIterator(const Table *table, std::vector<size_t>::const_iterator index, const std::vector<size_t> *indices) noexcept : _table(table), _index(index), _indices(indices) {}

		reference operator*() const { return ItemView(&((*_table)[*_index]), _indices); }
		reference operator[](difference_type n) const { return ItemView(&((*_table)[_index[n]]), _indices); }

		auto & operator++() noexcept { _index++; return *this; }
		auto & operator--() noexcept { _index--; return *this; }
		auto & operator+=(difference_type n) noexcept { _index += n; return *this; }
		auto & operator-=(difference_type n) noexcept { _index -= n; return *this; }

		auto operator++(int) noexcept { auto result = *this; ++*this; return result; }
		auto operator--(int) noexcept { auto result = *this; --*this; return result; }

		auto operator+(difference_type n) const noexcept{ auto result = *this; return result += n; }
		auto operator-(difference_type n) const noexcept { auto result = *this; return result -= n; }

		difference_type operator-(const TableIterator &iterator) const noexcept { return _index - iterator._index; }

		bool operator!=(const TableIterator &iterator) const noexcept { return _index != iterator._index; }
		bool operator<(const TableIterator &iterator) const noexcept { return _index < iterator._index; }
};

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

		TableIterator begin() const;
		TableIterator end() const;

		size_t items() const;
		size_t fields() const;

		void undo();
		void redo();
};

#endif
