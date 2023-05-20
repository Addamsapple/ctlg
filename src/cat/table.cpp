#include "table_actions.h"

#include "return.h"
#include "type_proc.h"
#include "item_sorter.h"

std::unique_ptr<Table::Action> Table::_insertItem(const std::string &item, const size_t position, const bool ignoreErrors) {
	setReturnCode(0, "");
	std::unique_ptr<Action> result;
	Item item_(item, _itemConstructor);
	if (returnCode() == 0 || ignoreErrors) {
		result = InsertItemAction(std::move(item_), position).perform(*this);
		if (returnCode() != 0) setReturnCode(0, "");
	} else
		setReturnCode(55555, returnMessage());
	return result;
}

std::unique_ptr<Table::Action> Table::_insertColumn(std::vector<std::string> &&fields, const size_t position) {
	setReturnCode(0, "");
	std::unique_ptr<Action> result;
	auto matchResult = typeProcessor.match(fields[0]);
	//if (typeProcessor.match(fields[0], &constructor) == FULL_MATCH_) {
	if (matchResult.first) {
		std::vector<std::unique_ptr<Field>> fields_;
		fields_.reserve(_header.size() + _items.size());
		fields_.emplace_back(new Field(std::move(fields[0])));
		fields_.emplace_back(new Field(std::move(fields[1])));
		for (size_t item = 0; item < items(); item++)
			fields_.emplace_back(matchResult.first->create(std::move(fields[item + _header.size()])));
		result = InsertColumnAction(std::move(fields_), std::unique_ptr<FieldFactory>(matchResult.first), position).perform(*this);
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
	std::unique_ptr<Action> result;
	if (item < items())
		result = DeleteItemAction(item).perform(*this);
	else
		setReturnCode(424242, "item x out of range");
	return result;
}

std::unique_ptr<Table::Action> Table::_setField(std::string &&field, size_t item, size_t column) {
	auto field_ = std::unique_ptr<Field>(_itemConstructor[column]->create(std::move(field)));
	if (returnCode() == 0)
		return SetFieldAction(std::move(field_), item, column).perform(*this);
	else
		return std::unique_ptr<Action>();
}

std::unique_ptr<Table::Action> Table::_setTitle(std::string &&title, const size_t position) {
	return SetTitleAction(std::make_unique<Field>(std::move(title)), position).perform(*this);
}

std::unique_ptr<Table::Action> Table::_sortItems(std::vector<size_t> &&columns) {
	return SetOrderAction(sortedOrder(_items, Compare<Item>(std::move(columns)))).perform(*this);
}

void Table::insertItem(const std::string &item, const size_t position, const bool ignoreErrors) { _insertItem(item, position, ignoreErrors); }
void Table::deleteItem(const size_t item) { _deleteItem(item); }
void Table::insertColumn(std::vector<std::string> &&fields, const size_t position) { _insertColumn(std::move(fields), position); }
void Table::deleteColumn(const size_t position) { _deleteColumn(position); }
void Table::SetField(std::string &&field, size_t item, size_t column) { _setField(std::move(field), item, column); }
void Table::setTitle(std::string &&title, const size_t position) { _setTitle(std::move(title), position); }

void Table::clear() {
	_header[0].clear();
	_header[1].clear();
	_items.clear();
	_itemConstructor.clear();
}

const Item & Table::types() const { return _header[0]; }
const Item & Table::titles() const { return _header[1]; }

const Item & Table::operator[](size_t item) const { return _items[item]; }

ConstItemIterator Table::begin() const { return _items.cbegin(); }
ConstItemIterator Table::end() const { return _items.cend(); }

size_t Table::items() const { return _items.size(); }
size_t Table::fields() const { return _header[0].size(); }
