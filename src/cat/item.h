#ifndef ITEM_H
#define ITEM_H

#include <memory>
#include <vector>

#include "field.h"

using StringVector = std::vector<std::string>;
using FieldVector = std::vector<std::unique_ptr<Field>>;
using FieldIterator = FieldVector::iterator;
using ConstFieldIterator = FieldVector::const_iterator;

using ItemConstructor = std::vector<std::unique_ptr<FieldFactory>>;

//make delete Field return deleted field?

class Item {
	protected:
		FieldVector _fields;

		Item(size_t fields);
	public:
		typedef std::unique_ptr<Field> value_type;

		Item() = default;
		
		//consider adding ignoreErrors parameter to constructors:
		//if !ignoredErrors, then don't go through the effort of constructing a proper Item
		//otherwise, do.

		Item(StringVector &&item, const ItemConstructor &constructor);
		Item(StringVector &&item, const size_t size);
		Item(StringVector &&item);

		Item(const std::string &string, const ItemConstructor &constructor);
		Item(const std::string &string, const size_t size);
		Item(const std::string &string);

		void insertField(std::string &&string, const FieldFactory &constructor, const size_t position);
		void insertField(std::string &&string, const size_t position);
		void insertField(std::unique_ptr<Field> &&field, const size_t position);

		void deleteField(const size_t position);
	
		std::unique_ptr<Field> & operator[](size_t field);
		//const Field & operator[](size_t field) const;
		const Field & get(size_t field) const;

		FieldIterator begin();
		FieldIterator end();
		ConstFieldIterator cbegin() const;
		ConstFieldIterator cend() const;

		size_t size() const;

		void clear();
};

std::string repeatField(const std::string &string, const size_t fields);

StringVector splitItem(const std::string &item);

std::ostream & operator<<(std::ostream &stream, const Item &item);

#endif
