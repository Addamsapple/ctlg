#ifndef CATALOGUE_H
#define CATALOGUE_H

#include <fstream>
#include <vector>

#include "item.h"

#include "actions.h"

using ItemVector = std::vector<Item>;
using ItemIterator = ItemVector::iterator;
using ConstItemIterator = ItemVector::const_iterator;

class Catalogue {
	protected:
		static const size_t _HEADER_ITEMS = 2;

		ItemVector _items;

		ItemConstructor _itemConstructor;

		template<typename T> std::unique_ptr<Action> _process(T &&action);

		std::unique_ptr<Action> _insertItem(const std::string &string, const size_t position, const bool ignoreErrors);
		std::unique_ptr<Action> _deleteItem(const size_t item);

		std::unique_ptr<Action> _insertColumn(std::vector<std::string> &&fields, const size_t position);
		std::unique_ptr<Action> _deleteColumn(const size_t position);

		std::unique_ptr<Action> _setTitle(std::string &&title, const size_t position);
	public:
		Catalogue();
		
		void insertItem(const std::string &string, const size_t position, const bool ignoreErrors);
		void deleteItem(const size_t item);

		void insertColumn(std::vector<std::string> &&fields, const size_t position);
		void deleteColumn(const size_t position);

		void setTitle(std::string &&title, const size_t position);

		const ItemConstructor & itemConstructor() const;

		std::unique_ptr<FieldConstructorInterface> & fieldConstructor(size_t column);

		Item & types();
		const Item & types() const;

		Item & titles();
		const Item & titles() const;

		Item & operator[](size_t item);
		const Item & operator[](size_t item) const;

		ItemIterator begin();
		ItemIterator end();
		//just call these methods begin() and end()???
		ConstItemIterator cbegin() const;
		ConstItemIterator cend() const;

		size_t size() const;
		size_t items() const;
		size_t fields() const;
};

#endif
