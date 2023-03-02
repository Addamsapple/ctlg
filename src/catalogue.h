#ifndef CATALOGUE_H
#define CATALOGUE_H

#include <vector>

#include "item.h"

using ItemVector = std::vector<Item>;
using ItemIterator = ItemVector::iterator;
using ConstItemIterator = ItemVector::const_iterator;

class Catalogue {
	protected:
		Item _typeHeader;
		Item _titleHeader;
		ItemVector _items;

		ItemConstructor _itemConstructor;
	public:
		void load(const std::string &file);

		Item & typeHeader();
		const Item & typeHeader() const;

		Item & titleHeader();
		const Item & titleHeader() const;

		Item & operator[](size_t item);
		const Item & operator[](size_t item) const;

		ItemIterator begin();
		ItemIterator end();
		ConstItemIterator cbegin() const;
		ConstItemIterator cend() const;

		size_t items() const;
		size_t fields() const;
};

#endif
