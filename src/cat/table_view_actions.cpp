#include "table_view_actions.h"

#include "table_view.h"

TableView::InsertItemAction::InsertItemAction(size_t item, size_t value) : _item(item), _value(value) {}

std::unique_ptr<TableView::Action> TableView::InsertItemAction::perform(TableView &view) {
	for (auto &val : view._items)
		if (val >= _value)
			val++;
	view._items.insert(view._items.begin() + _item, _value);
	return std::unique_ptr<TableView::Action>();
}

TableView::DeleteItemAction::DeleteItemAction(size_t item) : _item(item) {}

std::unique_ptr<TableView::Action> TableView::DeleteItemAction::perform(TableView &view) {
	auto result = std::make_unique<TableView::InsertItemAction>(_item, view._items[_item]);
	for (auto &val : view._items)
		if (val > view._items[_item])
			val--;
	view._items.erase(view._items.begin() + _item);
	return result;
}

TableView::InsertColumnAction::InsertColumnAction(size_t column, size_t value) : _column(column), _value(value) {}

std::unique_ptr<TableView::Action> TableView::InsertColumnAction::perform(TableView &view) {
	for (auto &val : view._fields)
		if (val >= _value)
			val++;
	view._fields.insert(view._fields.begin() + _column, _value);
	return std::make_unique<TableView::DeleteColumnAction>(_column);
}

TableView::DeleteColumnAction::DeleteColumnAction(size_t column) : _column(column) {}

std::unique_ptr<TableView::Action> TableView::DeleteColumnAction::perform(TableView &view) {
	auto result = std::make_unique<TableView::InsertColumnAction>(_column, view._fields[_column]);
	for (auto &val : view._fields)
		if (val > view._fields[_column])
			val--;
	view._fields.erase(view._fields.begin() + _column);
	return result;
}
