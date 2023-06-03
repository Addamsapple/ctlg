#include "table_view_actions.h"

TableView::InsertItemAction::InsertItemAction(size_t item, size_t value) : _item(item), _value(value) {}

std::unique_ptr<TableView::Action> TableView::InsertItemAction::perform(TableView &view) {
	
}

TableView::DeleteItemAction::DeleteItemAction(size_t item) : _item(item) {}

std::unique_ptr<TableView::Action> TableView::DeleteItemAction::perform(TableView &view) {

}

TableView::InsertColumnAction::InsertColumnAction(size_t column, size_t value) : _column(column), _value(value) {}

std::unique_ptr<TableView::Action> TableView::InsertColumnAction::perform(TableView &view) {

}

TableView::DeleteColumnAction::DeleteColumnAction(size_t column) : _column(column) {}

std::unique_ptr<TableView::Action> TableView::DeleteColumnAction::perform(TableView &view) {

}
