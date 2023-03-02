#ifndef ITEM_H
#define ITEM_H

#include <memory>
#include <vector>

#include "field.h"

using StringVector = std::vector<std::string>;
using FieldVector = std::vector<std::unique_ptr<Field>>;
using FieldIterator = FieldVector::iterator;
using ConstFieldIterator = FieldVector::const_iterator;

using ItemConstructor = std::vector<FieldConstructorInterface *>;

class Item{
	protected:
		FieldVector _fields;

		Item(size_t fields);
	public:
		Item() = default;
		Item(std::string &&string, const size_t size);
		Item(std::string &&string, const ItemConstructor &constructor);

		Field & operator[](size_t field);
		const Field & operator[](size_t field) const;

		FieldIterator begin();
		FieldIterator end();
		ConstFieldIterator cbegin() const;
		ConstFieldIterator cend() const;

		size_t size() const;
};

StringVector splitFields(std::string &&fields);

//need to throw an exception when a type is not matched, otherwise an error is detected during item creation, since there are more fields than valid types.
ItemConstructor makeItemConstructor(Item &item);

#endif
