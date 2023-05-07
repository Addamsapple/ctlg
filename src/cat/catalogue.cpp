#include "actions.h"

#include "return.h"
#include "type_proc.h"

Catalogue::Catalogue() : _items(HEADER_ITEMS), _itemConstructor(0) {}

std::unique_ptr<Catalogue::Action> Catalogue::_insertItem(const std::string &item, const size_t position, const bool ignoreErrors) {
	setReturnCode(0, "");
	std::unique_ptr<Catalogue::Action> result;
	Item item_(item, _itemConstructor);
	if (returnCode() == 0 || ignoreErrors) {
		result = InsertItemAction(std::move(item_), position + HEADER_ITEMS).perform(*this);
		if (returnCode() != 0) setReturnCode(0, "");
	} else
		setReturnCode(55555, returnMessage());
	return result;
}

std::unique_ptr<Catalogue::Action> Catalogue::_insertColumn(std::vector<std::string> &&fields, const size_t position) {
	setReturnCode(0, "");
	std::unique_ptr<Catalogue::Action> result;
	FieldConstructorInterface *constructor;
	if (typeProcessor.match(fields[0], constructor) == FULL_MATCH) {
		std::vector<std::unique_ptr<Field>> fields_;
		fields_.reserve(size());
		fields_.emplace_back(new Field(std::move(fields[0])));
		fields_.emplace_back(new Field(std::move(fields[1])));
		for (size_t item = 0; item < items(); item++)
			fields_.emplace_back(constructor->construct(std::move(fields[item + HEADER_ITEMS])));
		result = InsertColumnAction(std::move(fields_), std::unique_ptr<FieldConstructorInterface>(constructor), position).perform(*this);
	} else
		setReturnCode(2222, "Invalid column type");
	return result;
}

std::unique_ptr<Catalogue::Action> Catalogue::_deleteColumn(const size_t position) {
	setReturnCode(0, "");
	return DeleteColumnAction(position).perform(*this);
}

std::unique_ptr<Catalogue::Action> Catalogue::_deleteItem(const size_t item) {
	setReturnCode(0, "");
	std::unique_ptr<Catalogue::Action> result;
	if (item < items())
		result = DeleteItemAction(item + HEADER_ITEMS).perform(*this);
	else
		setReturnCode(424242, "item x out of range");
	return result;
}

std::unique_ptr<Catalogue::Action> Catalogue::_setTitle(std::string &&title, const size_t position) {
	return SetFieldAction(std::make_unique<Field>(std::move(title)), 1, position).perform(*this);
}

void Catalogue::insertItem(const std::string &item, const size_t position, const bool ignoreErrors) { _insertItem(item, position, ignoreErrors); }
void Catalogue::deleteItem(const size_t item) { _deleteItem(item); }
void Catalogue::insertColumn(std::vector<std::string> &&fields, const size_t position) { _insertColumn(std::move(fields), position); }
void Catalogue::deleteColumn(const size_t position) { _deleteColumn(position); }
void Catalogue::setTitle(std::string &&title, const size_t position) { _setTitle(std::move(title), position); }

const Item & Catalogue::types() const { return _items[0]; }
const Item & Catalogue::titles() const { return _items[1]; }

const Item & Catalogue::operator[](size_t item) const { return _items[item + HEADER_ITEMS]; }

ConstItemIterator Catalogue::begin() const { return _items.cbegin() + HEADER_ITEMS; }
ConstItemIterator Catalogue::end() const { return _items.cend(); }

size_t Catalogue::size() const { return _items.size(); }
size_t Catalogue::items() const { return _items.size() - HEADER_ITEMS; }
size_t Catalogue::fields() const { return _items[0].size(); }
