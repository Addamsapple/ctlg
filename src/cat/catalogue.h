#ifndef CATALOGUE_H
#define CATALOGUE_H

#include <vector>

#include "item.h"

using ItemVector = std::vector<Item>;
using ItemIterator = ItemVector::iterator;
using ConstItemIterator = ItemVector::const_iterator;

class Catalogue {
	protected:
		static const size_t HEADER_ITEMS = 2;//rename to include _ at start?

		ItemVector _items;
		ItemConstructor _itemConstructor;

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
		Catalogue();
		
		void insertItem(const std::string &string, const size_t position, const bool ignoreErrors);
		void deleteItem(const size_t item);
		void insertColumn(std::vector<std::string> &&fields, const size_t position);
		void deleteColumn(const size_t position);
		void setTitle(std::string &&title, const size_t position);

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
