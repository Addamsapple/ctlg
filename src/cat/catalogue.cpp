//#include <fstream>

#include "catalogue.h"
#include "return.h"
#include "type_proc.h"

template<typename T>
void Catalogue::setTypes(T string) {//call rename argument to item????
	setReturnCode(0, "");
	Item typeHeader_ = Item(std::move(string), 0);
	auto itemConstructor_ = makeItemConstructor(typeHeader_);
	if (returnCode() == 0) {
		_types = std::move(typeHeader_);
		_itemConstructor = std::move(itemConstructor_);
	} else
		setReturnCode(CATALOGUE_TYPE_HEADER_ERROR, "invalid type header" + returnMessage());
}

template void Catalogue::setTypes(const std::string &string);
template void Catalogue::setTypes<StringVector &>(StringVector &string);

void Catalogue::setTitles(const std::string &string) {//rename argument to item???
	setReturnCode(0, "");
	Item titleHeader_(string, fields());//rename to titles???
	if (returnCode() == 0)
		_titles = std::move(titleHeader_);
	else
		setReturnCode(111111, "invalid title header" + returnMessage());
}

void Catalogue::insertItem(Item &&item, const size_t position) {
	_items.insert(begin() + position, std::move(item));
}

void Catalogue::insertItem(const std::string &item, const size_t position, const bool ignoreErrors) {
	setReturnCode(0, "");
	Item item_(item, _itemConstructor);
	if (returnCode() == 0 || ignoreErrors) {
		insertItem(std::move(item_), position);
		if (returnCode() != 0)
			setReturnCode(0, "");
	} else
		setReturnCode(55555, returnMessage());
}

void Catalogue::appendItem(const std::string &item, const bool ignoreErrors) {
	insertItem(item, items(), ignoreErrors);
}

//get rid of title parameter, handle with separate function
//could probably get rid of makeItemConstructor methods and reuse the code in here
void Catalogue::insertColumn(std::unique_ptr<Field> &&type, std::unique_ptr<Field> &&title, const size_t position) {
	setReturnCode(0, "");
	FieldConstructorInterface *constructor;
	if (typeProcessor.match(type->string(), constructor) == FULL_MATCH) {
		for (auto item = begin(); item != end(); item++)
			item->insertField("", *constructor, position);
		_types.insertField(std::move(type), position);
		_titles.insertField(std::move(title), position);
		_itemConstructor.insert(_itemConstructor.begin() + position, std::unique_ptr<FieldConstructorInterface>(constructor));
	} else {
		setReturnCode(2222, "Invalid column type");
	}
}

void Catalogue::insertColumn(std::unique_ptr<Field> &&type, std::unique_ptr<Field> &&title, std::vector<std::unique_ptr<Field>> &fields, const size_t position) {
	setReturnCode(0, "");
	FieldConstructorInterface *constructor;
	if (typeProcessor.match(type->string(), constructor) == FULL_MATCH) {
		for (size_t item = 0; item < items(); item++)
			_items[item].insertField(std::move(fields[item]), position);
		_types.insertField(std::move(type), position);
		_titles.insertField(std::move(title), position);
		_itemConstructor.insert(_itemConstructor.begin() + position, std::unique_ptr<FieldConstructorInterface>(constructor));
	} else {
		setReturnCode(2222, "Invalid column type");
	}
}

void Catalogue::deleteColumn(const size_t position) {
	for (auto item = begin(); item != end(); item++)
		item->deleteField(position);
	_types.deleteField(position);
	_titles.deleteField(position);
	_itemConstructor.erase(_itemConstructor.begin() + position);
}

void Catalogue::deleteItem(const size_t item) {
	setReturnCode(0, "");
	if (item < items())
		_items.erase(begin() + item);
	else
		setReturnCode(424242, "item x out of range");
}

const ItemConstructor & Catalogue::itemConstructor() const {
	return _itemConstructor;
}

Item & Catalogue::types() {
	return _types;
}

const Item & Catalogue::types() const {
	return _types;
}

Item & Catalogue::titles() {
	return _titles;
}

const Item & Catalogue::titles() const {
	return _titles;
}


std::unique_ptr<FieldConstructorInterface> & Catalogue::fieldConstructor(size_t column) {
	return _itemConstructor[column];
}

Item & Catalogue::operator[](size_t item) {
	return _items[item];
}

const Item & Catalogue::operator[](size_t item) const {
	return _items[item];
}

ItemIterator Catalogue::begin() {
	return _items.begin();
}

ItemIterator Catalogue::end() {
	return _items.end();
}

ConstItemIterator Catalogue::cbegin() const {
	return _items.cbegin();
}

ConstItemIterator Catalogue::cend() const {
	return _items.cend();
}

size_t Catalogue::items() const {
	return _items.size();
}

size_t Catalogue::fields() const {
	return _types.size();
}
