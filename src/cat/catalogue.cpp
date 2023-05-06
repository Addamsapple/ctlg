//#include <fstream>

#include "catalogue.h"
#include "return.h"
#include "type_proc.h"

Catalogue::Catalogue() : _items(HEADER_ITEMS), _itemConstructor(0) {}

std::unique_ptr<Action> Catalogue::insertItem(const std::string &item, const size_t position, const bool ignoreErrors) {
	setReturnCode(0, "");
	std::unique_ptr<Action> result;
	Item item_(item, _itemConstructor);
	if (returnCode() == 0 || ignoreErrors) {
		result = process(InsertItemAction(std::move(item_), position + HEADER_ITEMS));
		if (returnCode() != 0)
			setReturnCode(0, "");
	} else
		setReturnCode(55555, returnMessage());
	return result;
}

void Catalogue::insertItem(const std::string &item, const size_t position, const bool ignoreErrors) { _insertItem(item, position, ignoreErrors); }

std::unique_ptr<Action> Catalogue::insertColumn(std::vector<std::string> &&fields, const size_t position) {
	setReturnCode(0, "");
	std::unique_ptr<Action> result;
	FieldConstructorInterface *constructor;
	if (typeProcessor.match(fields[0], constructor) == FULL_MATCH) {
		std::vector<std::unique_ptr<Field>> fields_;
		fields_.reserve(size());
		fields_.emplace_back(new Field(std::move(fields[0])));
		fields_.emplace_back(new Field(std::move(fields[1])));
		for (size_t item = 0; item < items(); item++)
			fields_.emplace_back(constructor->construct(std::move(fields[item + HEADER_ITEMS])));
		result = process(InsertColumnAction(std::move(fields_), std::unique_ptr<FieldConstructorInterface>(constructor), position));
	} else
		setReturnCode(2222, "Invalid column type");
	return result;
}

void Catalogue::insertColumn(std::vector<std::string &&fields, const size_t position) { _insertColumn(std::move(fields), position); }

std::unique_ptr<Action> Catalogue::deleteColumn(const size_t position) {
	setReturnCode(0, "");
	return process(DeleteColumnAction(position));
}

void Catalogue::deleteColumn(const size_t position) { _deleteColumn(position); }

std::unique_ptr<Action> Catalogue::deleteItem(const size_t item) {
	setReturnCode(0, "");
	std::unique_ptr<Action> result;
	if (item < items())
		result = process(DeleteItemAction(item + HEADER_ITEMS));
	else
		setReturnCode(424242, "item x out of range");
	return result;
}

void Catalogue::deleteItem(const size_t item) { _deleteItem(item); }

std::unique_ptr<Action> Catalogue::setTitle(std::string &&title, const size_t position) {
	return process(SetFieldAction(std::make_unique<Field>(std::move(title)), 1, position));
}

void Catalogue::setTitle(std::string &&title, const size_t position) { _setTitle(std::move(title), position); }


const ItemConstructor & Catalogue::itemConstructor() const { return _itemConstructor; }

Item & Catalogue::types() { return _items[0]; }

const Item & Catalogue::types() const { return _items[0]; }

Item & Catalogue::titles() { return _items[1]; }

const Item & Catalogue::titles() const { return _items[1]; }

std::unique_ptr<FieldConstructorInterface> & Catalogue::fieldConstructor(size_t column) { return _itemConstructor[column]; }

Item & Catalogue::operator[](size_t item) { return _items[item + HEADER_ITEMS]; }

const Item & Catalogue::operator[](size_t item) const { return _items[item + HEADER_ITEMS]; }

ItemIterator Catalogue::begin() { return _items.begin() + HEADER_ITEMS; }

ItemIterator Catalogue::end() { return _items.end(); }

ConstItemIterator Catalogue::cbegin() const { return _items.cbegin() + HEADER_ITEMS; }

ConstItemIterator Catalogue::cend() const { return _items.cend(); }

size_t Catalogue::size() const { return _items.size(); }

size_t Catalogue::items() const { return _items.size() - HEADER_ITEMS; }

size_t Catalogue::fields() const { return _items[0].size(); }
