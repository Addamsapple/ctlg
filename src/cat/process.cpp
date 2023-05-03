#include "catalogue.h"

template<>
std::unique_ptr<Action> Catalogue::process(Action &&action) {
	return action.delegate(*this);
}

template<>
std::unique_ptr<Action> Catalogue::process(InsertItemAction &&action) {
	_items.insert(_items.begin() + action._index, std::move(action._item));
	return std::unique_ptr<Action>(new DeleteItemAction(action._index));
}

template<>
std::unique_ptr<Action> Catalogue::process(InsertColumnAction &&action) {
	for (auto item = 0; item < size(); item++)
		_items[item].insertField(std::move(action._fields[item]), action._column);
	_itemConstructor.insert(_itemConstructor.begin() + action._column, std::move(action._fieldConstructor));
	return std::unique_ptr<Action>(new DeleteColumnAction(action._column));
}

template<>
std::unique_ptr<Action> Catalogue::process(DeleteItemAction &&action) {
	auto result = std::unique_ptr<Action>(new InsertItemAction(std::move(_items[action._item]), action._item));
	_items.erase(_items.begin() + action._item);
	return result;
}

template<>
std::unique_ptr<Action> Catalogue::process(DeleteColumnAction &&action) {
	std::vector<std::unique_ptr<Field>> fields;
	fields.reserve(size());
	for (auto item = 0; item < size(); item++) {
		fields.push_back(std::move(_items[item][action._column]));
		_items[item].deleteField(action._column);
	}
	auto result = std::unique_ptr<Action>(new InsertColumnAction(std::move(fields), std::move(_itemConstructor[action._column]), action._column));
	_itemConstructor.erase(_itemConstructor.begin() + action._column);
	return result;
}

template<>
std::unique_ptr<Action> Catalogue::process(SetFieldAction &&action) {
	auto result = std::unique_ptr<Action>(new SetFieldAction(std::move(_items[action._item][action._column]), action._item, action._column));
	_items[action._item][action._column] = std::move(action._field);
	return result;
}
