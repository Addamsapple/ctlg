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
		Item _typeHeader;
		Item _titleHeader;
		ItemVector _items;

		ItemConstructor _itemConstructor;
	public:
		template<typename T> void setTypes(T string);
		void setTitles(const std::string &string);

		void insertItem(Item &&item, const size_t position);
		void insertItem(const std::string &string, const size_t position, const bool ignoreErrors);
		void appendItem(const std::string &string, const bool ignoreErrors);

		void deleteItem(const size_t item);

		void insertColumn(std::string &&type, const size_t position);

		void deleteColumn(const size_t position);

		void save(const std::string &);

		Item & typeHeader();
		const Item & typeHeader() const;

		Item & titleHeader();
		const Item & titleHeader() const;

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
