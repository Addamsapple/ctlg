#include "table_actions.h"

#include "return.h"
#include "type_proc.h"

Table::Table() : _items(_HEADER_ITEMS), _itemConstructor(0) {}

std::unique_ptr<Table::Action> Table::_insertItem(const std::string &item, const size_t position, const bool ignoreErrors) {
	setReturnCode(0, "");
	std::unique_ptr<Table::Action> result;
	Item item_(item, _itemConstructor);
	if (returnCode() == 0 || ignoreErrors) {
		result = InsertItemAction(std::move(item_), position + _HEADER_ITEMS).perform(*this);
		if (returnCode() != 0) setReturnCode(0, "");
	} else
		setReturnCode(55555, returnMessage());
	return result;
}

std::unique_ptr<Table::Action> Table::_insertColumn(std::vector<std::string> &&fields, const size_t position) {
	setReturnCode(0, "");
	std::unique_ptr<Table::Action> result;
	FieldConstructorInterface *constructor;
	if (typeProcessor.match(fields[0], constructor) == FULL_MATCH) {
		std::vector<std::unique_ptr<Field>> fields_;
		fields_.reserve(size());
		fields_.emplace_back(new Field(std::move(fields[0])));
		fields_.emplace_back(new Field(std::move(fields[1])));
		for (size_t item = 0; item < items(); item++)
			fields_.emplace_back(constructor->construct(std::move(fields[item + _HEADER_ITEMS])));
		result = InsertColumnAction(std::move(fields_), std::unique_ptr<FieldConstructorInterface>(constructor), position).perform(*this);
	} else
		setReturnCode(2222, "Invalid column type");
	return result;
}

std::unique_ptr<Table::Action> Table::_deleteColumn(const size_t position) {
	setReturnCode(0, "");
	return DeleteColumnAction(position).perform(*this);
}

std::unique_ptr<Table::Action> Table::_deleteItem(const size_t item) {
	setReturnCode(0, "");
	std::unique_ptr<Table::Action> result;
	if (item < items())
		result = DeleteItemAction(item + _HEADER_ITEMS).perform(*this);
	else
		setReturnCode(424242, "item x out of range");
	return result;
}

std::unique_ptr<Table::Action> Table::_setTitle(std::string &&title, const size_t position) {
	return SetFieldAction(std::make_unique<Field>(std::move(title)), 1, position).perform(*this);
}

std::unique_ptr<Table::Action> Table::_sortItems(std::vector<int> &&columns) {
	sortedOrder(_items, Compare<Item>({2, 3}));
}

void Table::insertItem(const std::string &item, const size_t position, const bool ignoreErrors) { _insertItem(item, position, ignoreErrors); }
void Table::deleteItem(const size_t item) { _deleteItem(item); }
void Table::insertColumn(std::vector<std::string> &&fields, const size_t position) { _insertColumn(std::move(fields), position); }
void Table::deleteColumn(const size_t position) { _deleteColumn(position); }
void Table::setTitle(std::string &&title, const size_t position) { _setTitle(std::move(title), position); }

const Item & Table::types() const { return _items[0]; }
const Item & Table::titles() const { return _items[1]; }

const Item & Table::operator[](size_t item) const { return _items[item + _HEADER_ITEMS]; }

ConstItemIterator Table::begin() const { return _items.cbegin() + _HEADER_ITEMS; }
ConstItemIterator Table::end() const { return _items.cend(); }

size_t Table::size() const { return _items.size(); }
size_t Table::items() const { return _items.size() - _HEADER_ITEMS; }
size_t Table::fields() const { return _items[0].size(); }