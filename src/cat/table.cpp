#include "table_actions.h"

#include "return.h"
#include "type_proc.h"
#include "item_sorter.h"

/*std::unique_ptr<Table::Action> Table::_sortItems(std::vector<size_t> &&columns) {
	return SetOrderAction(sortedOrder(_items, Compare<Item>(std::move(columns)))).perform(*this);
}*/

void Table::_record(std::unique_ptr<Table::Action> &&action) {
	if (action) {
		_redoableActions.clear();
		_undoableActions.push_back(std::move(action));
	}
}

bool Table::insertItem(const std::string &item, const size_t position, const bool ignoreErrors) {
	setReturnCode(0, "");
	Item item_(item, _itemConstructor);
	if (returnCode() == 0 || ignoreErrors) {
		_record(InsertItemAction(std::move(item_), position).perform(*this));
		if (returnCode() != 0)
			setReturnCode(0, "");
		return true;
	} else
		setReturnCode(55555, returnMessage());
	return false;
}

bool Table::deleteItem(const size_t item) {
	setReturnCode(0, "");
	if (item < items()) {
		_record(DeleteItemAction(item).perform(*this));
		return true;
	} else
		setReturnCode(424242, "item x out of range");
	return false;
}

bool Table::insertColumn(std::vector<std::string> &&fields, const size_t position) {
	setReturnCode(0, "");
	auto matchResult = typeProcessor.match(fields[0]);
	if (matchResult.first) {
		std::vector<std::unique_ptr<Field>> fields_;
		fields_.reserve(_header.size() + _items.size());
		fields_.emplace_back(new Field(std::move(fields[0])));
		fields_.emplace_back(new Field(std::move(fields[1])));
		for (size_t item = 0; item < items(); item++)
			fields_.emplace_back(matchResult.first->create(std::move(fields[item + _header.size()])));
		_record(InsertColumnAction(std::move(fields_), std::move(matchResult.first), position).perform(*this));
		return true;
	} else
		setReturnCode(2222, "Invalid column type");
	return false;
}

bool Table::deleteColumn(const size_t position) {
	setReturnCode(0, "");
	_record(DeleteColumnAction(position).perform(*this));
	return true;
}

bool Table::setField(std::string &&field, size_t item, size_t column) {
	auto field_ = std::unique_ptr<Field>(_itemConstructor[column]->create(std::move(field)));
	if (returnCode() == 0) {
		_record(SetFieldAction(std::move(field_), item, column).perform(*this));
		return true;
	}
	return false;
}

bool Table::setTitle(std::string &&title, const size_t position) {
	_record(SetTitleAction(std::make_unique<Field>(std::move(title)), position).perform(*this));
	return true;
}

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

void Table::undo() {
	if (_undoableActions.size() > 0) {
		_redoableActions.push_back(_undoableActions.back()->perform(*this));
		_undoableActions.pop_back();
	}
}

void Table::redo() {
	if (_redoableActions.size() > 0) {
		_undoableActions.push_back(_redoableActions.back()->perform(*this));
		_redoableActions.pop_back();
	}
}
