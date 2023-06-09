#include "table_view_actions.h"

void TableView::_record(TableView::record_type &&action) {
	if (action.first || action.second) {
		_redoableActions.clear();
		_undoableActions.push_back(std::move(action));
	}
}

void TableView::insertItem(const std::string &string, const size_t position, const bool ignoreErrors) {
	if (_table.insertItem(string, _table.items(), ignoreErrors))
		_record(std::make_pair(InsertItemAction(position, _table.items() - 1).perform(*this), true));
}

void TableView::deleteItem(const size_t item) {
	if (_table.deleteItem(_items[item]))
		_record(std::make_pair(DeleteItemAction(item).perform(*this), true));
}

void TableView::insertColumn(std::vector<std::string> &&fields, const size_t position) {
	if (_table.insertColumn(std::move(fields), _table.fields()))
		_record(std::make_pair(InsertColumnAction(position, _table.fields() - 1).perform(*this), true));
}

void TableView::deleteColumn(const size_t position) {
	if (_table.deleteColumn(_fields[position]))
		_record(std::make_pair(DeleteColumnAction(position).perform(*this), true));
}

void TableView::setField(std::string &&field, size_t item, size_t column) {
	if (_table.setField(std::move(field), _items[item], _fields[column]))
		_record(std::make_pair(std::unique_ptr<Action>(), true));
}

void TableView::setTitle(std::string &&title, const size_t position) {
	if (_table.setTitle(std::move(title), _fields[position]))
		_record(std::make_pair(std::unique_ptr<Action>(), true));
}

//void TableView::clear();

ItemView TableView::types() const { return ItemView(&(_table.types()), &_fields) ;}
ItemView TableView::titles() const { return ItemView(&(_table.titles()), &_fields); }

//should not return raw item, but rather a vector of std::refs?
//const Item & TableView::operator[](size_t item) const { return _table[item]; }

const Field & TableView::field(size_t row, size_t column) const { return _table[_items[row]].get(_fields[column]); }

TableViewIterator TableView::begin() const { return TableViewIterator(&_table, _items.begin(), &_fields); }
TableViewIterator TableView::end() const { return TableViewIterator(&_table, _items.end(), &_fields); }//could use nullptr in place of &_fields

size_t TableView::items() const { return _items.size(); }
size_t TableView::fields() const { return _fields.size(); }

void TableView::undo() {
	if (_undoableActions.size() > 0) {
		if (_undoableActions.back().second)
			_table.undo();
		std::unique_ptr<Action> action;
		if (_undoableActions.back().first)
			action = _undoableActions.back().first->perform(*this);
		_redoableActions.push_back(std::make_pair(std::move(action), _undoableActions.back().second));
		_undoableActions.pop_back();
	}
}

void TableView::redo() {
	if (_redoableActions.size() > 0) {
		if (_redoableActions.back().second)
			_table.redo();
		std::unique_ptr<Action> action;
		if (_redoableActions.back().first)
			action = _redoableActions.back().first->perform(*this);
		_undoableActions.push_back(std::make_pair(std::move(action), _redoableActions.back().second));
		_redoableActions.pop_back();
	}
}

void TableView::clear() {

}
