#ifndef CATALOGUE_H
#define CATALOGUE_H

#include <fstream>
#include <vector>

#include "item.h"

using ItemVector = std::vector<Item>;
using ItemIterator = ItemVector::iterator;
using ConstItemIterator = ItemVector::const_iterator;

class Catalogue {
	protected:
		//rename to _types, _titles?
		Item _types;
		Item _titles;
		ItemVector _items;

		ItemConstructor _itemConstructor;
	public:
		//rename to load types?
		template<typename T> void setTypes(T string);
		//rename to load titles?
		void setTitles(const std::string &string);

		void insertItem(Item &&item, const size_t position);
		void insertItem(const std::string &string, const size_t position, const bool ignoreErrors);

		//why have an appendItem at all, can be handled by insertItem no?
		void appendItem(const std::string &string, const bool ignoreErrors);

		void deleteItem(const size_t item);

		void insertColumn(std::unique_ptr<Field> &&type, std::unique_ptr<Field> &&title, std::vector<std::unique_ptr<Field>> &fields, const size_t position);
		void insertColumn(std::unique_ptr<Field> &&type, std::unique_ptr<Field> &&title, const size_t position);

		void deleteColumn(const size_t position);

		void save(const std::string &);

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

		size_t items() const;
		size_t fields() const;
};

#endif
