#include "table_actions.h"

#include "table.h"

//make order consistent with class declaration order

Table::InsertItemAction::InsertItemAction(Item &&item, size_t index) :
		_item(std::move(item)),
		_index(index) {}

std::unique_ptr<Table::Action> Table::InsertItemAction::perform(Table &table) {
	table._items.insert(table._items.begin() + _index, std::move(_item));
	return std::unique_ptr<Table::Action>(new DeleteItemAction(_index));
}

Table::InsertColumnAction::InsertColumnAction(std::vector<std::unique_ptr<Field>> &&fields, std::unique_ptr<FieldConstructorInterface> &&fieldConstructor, size_t column) :
		_fields(std::move(fields)),
		_fieldConstructor(std::move(fieldConstructor)),
		_column(column) {}

std::unique_ptr<Table::Action> Table::InsertColumnAction::perform(Table &table) {
	for (auto item = 0; item < table._items.size(); item++)
		table._items[item].insertField(std::move(_fields[item]), _column);
	table._itemConstructor.insert(table._itemConstructor.begin() + _column, std::move(_fieldConstructor));
	return std::unique_ptr<Table::Action>(new DeleteColumnAction(_column));
}

Table::DeleteItemAction::DeleteItemAction(size_t item) : _item(item) {}

std::unique_ptr<Table::Action> Table::DeleteItemAction::perform(Table &table) {
	auto result = std::unique_ptr<Table::Action>(new InsertItemAction(std::move(table._items[_item]),_item));
	table._items.erase(table._items.begin() + _item);
	return result;
}

Table::DeleteColumnAction::DeleteColumnAction(size_t column) : _column(column) {}

std::unique_ptr<Table::Action> Table::DeleteColumnAction::perform(Table &table) {
	std::vector<std::unique_ptr<Field>> fields;
	fields.reserve(table._items.size());
	for (auto item = 0; item < table._items.size(); item++) {
		fields.push_back(std::move(table._items[item][_column]));
		table._items[item].deleteField(_column);
	}
	auto result = std::unique_ptr<Table::Action>(new InsertColumnAction(std::move(fields), std::move(table._itemConstructor[_column]), _column));
	table._itemConstructor.erase(table._itemConstructor.begin() + _column);
	return result;
}

Table::SetFieldAction::SetFieldAction(std::unique_ptr<Field> &&field, size_t item, size_t column) :
		_field(std::move(field)),
		_item(item),
		_column(column) {}

std::unique_ptr<Table::Action> Table::SetFieldAction::perform(Table &table) {
	auto result = std::unique_ptr<Table::Action>(new SetFieldAction(std::move(table._items[_item][_column]), _item, _column));
	table._items[_item][_column] = std::move(_field);
	return result;
}
