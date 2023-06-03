#ifndef CATALOGUE_H
#define CATALOGUE_H

#include <array>
#include <vector>

#include "item.h"

using ItemVector = std::vector<Item>;
using ItemIterator = ItemVector::iterator;
using ConstItemIterator = ItemVector::const_iterator;

class Table {
	private:
		std::array<Item, 2> _header;
		std::vector<Item> _items;
		ItemConstructor _itemConstructor;

		class Action;

		std::vector<std::unique_ptr<Action>> _undoableActions;
		std::vector<std::unique_ptr<Action>> _redoableActions;

		class InsertItemAction;
		class DeleteItemAction;
		class InsertColumnAction;
		class DeleteColumnAction;
		class SetFieldAction;
		class SetTitleAction;
		class SetOrderAction;

		void _record(std::unique_ptr<Action> &&action);
	public:
		bool insertItem(const std::string &string, const size_t position, const bool ignoreErrors);
		bool deleteItem(const size_t item);
		bool insertColumn(std::vector<std::string> &&fields, const size_t position);
		bool deleteColumn(const size_t position);
		bool setField(std::string &&field, size_t item, size_t column);
		bool setTitle(std::string &&title, const size_t position);

		void clear();
		//void setType()???

		const Item & types() const;
		const Item & titles() const;

		const Item & operator[](size_t item) const;

		ConstItemIterator begin() const;
		ConstItemIterator end() const;

		size_t items() const;
		size_t fields() const;

		void undo();
		void redo();
};

#endif
