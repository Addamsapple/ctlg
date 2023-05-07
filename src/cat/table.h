#ifndef CATALOGUE_H
#define CATALOGUE_H

#include <vector>

#include "item.h"

using ItemVector = std::vector<Item>;
using ItemIterator = ItemVector::iterator;
using ConstItemIterator = ItemVector::const_iterator;

class Table {
	private:
		static const size_t _HEADER_ITEMS = 2;

		ItemVector _items;
		ItemConstructor _itemConstructor;
	protected:
		class Action;

		std::unique_ptr<Action> _insertItem(const std::string &string, const size_t position, const bool ignoreErrors);
		std::unique_ptr<Action> _deleteItem(const size_t item);
		std::unique_ptr<Action> _insertColumn(std::vector<std::string> &&fields, const size_t position);
		std::unique_ptr<Action> _deleteColumn(const size_t position);
		std::unique_ptr<Action> _setTitle(std::string &&title, const size_t position);

		class InsertItemAction;
		class DeleteItemAction;
		class InsertColumnAction;
		class DeleteColumnAction;
		class SetFieldAction;
	public:
		Table();
		
		void insertItem(const std::string &string, const size_t position, const bool ignoreErrors);
		void deleteItem(const size_t item);
		void insertColumn(std::vector<std::string> &&fields, const size_t position);
		void deleteColumn(const size_t position);
		void setTitle(std::string &&title, const size_t position);
		//void setField()
		//void setType()???

		const Item & types() const;
		const Item & titles() const;

		const Item & operator[](size_t item) const;

		ConstItemIterator begin() const;
		ConstItemIterator end() const;

		size_t size() const;
		size_t items() const;
		size_t fields() const;
};

#endif
