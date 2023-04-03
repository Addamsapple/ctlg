//#include <fstream>

#include "catalogue.h"
#include "return.h"

template<typename T>
void Catalogue::setTypes(T string) {//call rename argument to item????
	setReturnCode(0, "");
	Item typeHeader_ = Item(std::move(string), 0);
	auto itemConstructor_ = makeItemConstructor(typeHeader_);
	if (returnCode() == 0) {
		_typeHeader = std::move(typeHeader_);
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
		_titleHeader = std::move(titleHeader_);
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

void Catalogue::deleteItem(const size_t item) {
	setReturnCode(0, "");
	if (item < items())
		_items.erase(begin() + item);
	else
		setReturnCode(424242, "item x out of range");
}

Item & Catalogue::typeHeader() {
	return _typeHeader;
}

const Item & Catalogue::typeHeader() const {
	return _typeHeader;
}

Item & Catalogue::titleHeader() {
	return _titleHeader;
}

const Item & Catalogue::titleHeader() const {
	return _titleHeader;
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
	return _typeHeader.size();
}
