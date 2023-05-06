#include "actions.h"

#include "catalogue.h"

Catalogue::InsertItemAction::InsertItemAction(Item &&item, size_t index) :
		_item(std::move(item)),
		_index(index) {}

std::unique_ptr<Catalogue::Action> Catalogue::InsertItemAction::perform(Catalogue &catalogue) {
	catalogue._items.insert(catalogue._items.begin() + _index, std::move(_item));
	//_items.insert(_items.begin() + action._index, std::move(action._item));
	return std::unique_ptr<Catalogue::Action>(new DeleteItemAction(_index));
	//return std::unique_ptr<Catalogue::Action>(new DeleteItemAction(action._index));
}

Catalogue::InsertColumnAction::InsertColumnAction(std::vector<std::unique_ptr<Field>> &&fields, std::unique_ptr<FieldConstructorInterface> &&fieldConstructor, size_t column) :
		_fields(std::move(fields)),
		_fieldConstructor(std::move(fieldConstructor)),
		_column(column) {}

std::unique_ptr<Catalogue::Action> Catalogue::InsertColumnAction::perform(Catalogue &catalogue) {
	//for (auto item = 0; item < size(); item++)
	for (auto field = 0; field < _fields.size(); field++)//rename field to item?
		catalogue._items[field].insertField(std::move(_fields[field]), _column);
		//_items[item].insertField(std::move(action._fields[item]), action._column);
	//_itemConstructor.insert(_itemConstructor.begin() + action._column, std::move(action._fieldConstructor));
	catalogue._itemConstructor.insert(catalogue._itemConstructor.begin() + _column, std::move(_fieldConstructor));
	//return std::unique_ptr<Catalogue::Action>(new DeleteColumnAction(action._column));
	return std::unique_ptr<Catalogue::Action>(new DeleteColumnAction(_column));
}

Catalogue::DeleteItemAction::DeleteItemAction(size_t item) :
		_item(item) {}

std::unique_ptr<Catalogue::Action> Catalogue::DeleteItemAction::perform(Catalogue &catalogue) {
	//auto result = std::unique_ptr<Catalogue::Action>(new InsertItemAction(std::move(_items[action._item]), action._item));
	auto result = std::unique_ptr<Catalogue::Action>(new InsertItemAction(std::move(catalogue._items[_item]),_item));
	//_items.erase(_items.begin() + action._item);
	catalogue._items.erase(catalogue._items.begin() + _item);
	return result;
}

Catalogue::DeleteColumnAction::DeleteColumnAction(size_t column) :
		_column(column) {}

std::unique_ptr<Catalogue::Action> Catalogue::DeleteColumnAction::perform(Catalogue &catalogue) {
	std::vector<std::unique_ptr<Field>> fields;
	//fields.reserve(size());
	fields.reserve(catalogue._items.size());
	for (auto item = 0; item < catalogue._items.size(); item++) {//rename item to field?
		//fields.push_back(std::move(_items[item][action._column]));
		fields.push_back(std::move(catalogue._items[item][_column]));
		//_items[item].deleteField(action._column);
		catalogue._items[item].deleteField(_column);
	}
	//auto result = std::unique_ptr<Catalogue::Action>(new InsertColumnAction(std::move(fields), std::move(_itemConstructor[action._column]), action._column));
	auto result = std::unique_ptr<Catalogue::Action>(new InsertColumnAction(std::move(fields), std::move(catalogue._itemConstructor[_column]), _column));
	//_itemConstructor.erase(_itemConstructor.begin() + action._column);
	catalogue._itemConstructor.erase(catalogue._itemConstructor.begin() + _column);
	return result;
}

Catalogue::SetFieldAction::SetFieldAction(std::unique_ptr<Field> &&field, size_t item, size_t column) :
		_field(std::move(field)),
		_item(item),
		_column(column) {}

std::unique_ptr<Catalogue::Action> Catalogue::SetFieldAction::perform(Catalogue &catalogue) {
	//auto result = std::unique_ptr<Catalogue::Action>(new SetFieldAction(std::move(_items[action._item][action._column]), action._item, action._column));
	auto result = std::unique_ptr<Catalogue::Action>(new SetFieldAction(std::move(catalogue._items[_item][_column]), _item, _column));
	//_items[action._item][action._column] = std::move(action._field);
	catalogue._items[_item][_column] = std::move(_field);
	return result;
}
