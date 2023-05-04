#ifndef CATALOGUE_H
#define CATALOGUE_H

#include <fstream>
#include <vector>

#include "item.h"

#include "actions.h"

using ItemVector = std::vector<Item>;
using ItemIterator = ItemVector::iterator;
using ConstItemIterator = ItemVector::const_iterator;

//define a column struct to be used for passing arguments, 
//
//consider making privete nested class called something to manage construction and restoring of catalogue mementos
//it should be able to construct mementos given mainly index arguments.
//it should also be able to restore said mementos  ...?
//

//consider making Catalogue an abstract base class that excludes the public interfaces (deleteItem, insertItem, insertColumn, setField, etc...)
//make the rest of the class protected
//then the sub class will just define public interfaces and handle error checking and delegate the actual work to the process methods
//would probably have to make Action classes public to allow derived Catalogue class to construct
class Catalogue {
	friend class ActionProcessor;
	protected:
		//	just need to modify accessing, so that users cannot access title and type directly, i.e. offset input position by two, make items() return - 2 as well, etc, etc.
		ItemVector _items;

		ItemConstructor _itemConstructor;

	public:
		Catalogue();
		static const size_t HEADER_ITEMS = 2;

		//void insertItem(const std::string &string, const size_t position, const bool ignoreErrors);
		std::unique_ptr<Action> insertItem(const std::string &string, const size_t position, const bool ignoreErrors);

		//why have an appendItem at all, can be handled by insertItem no?
		void appendItem(const std::string &string, const bool ignoreErrors);

		//ItemMemento deleteItem(const size_t item);
		std::unique_ptr<Action> deleteItem(const size_t item);

		//maybe just group type and title into vector as well? to reduce number of parameters
		std::unique_ptr<Action> insertColumn(std::string &&type, std::string &&title, std::vector<std::string> &&fields, const size_t position);

		//void deleteColumn(const size_t position);
		std::unique_ptr<Action> deleteColumn(const size_t position);

		std::unique_ptr<Action> setTitle(std::string &&title, const size_t position);

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

		size_t size() const;
		size_t items() const;
		size_t fields() const;

		template<typename T> std::unique_ptr<Action> process(T &&action);
};

#endif
