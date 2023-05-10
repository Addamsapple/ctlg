#include "undoable_table.h"

#include "table_actions.h"

//need error checking here

void UndoableTable::_record(std::unique_ptr<Table::Action> &&action) {
	_redoableActions.clear();
	_undoableActions.push_back(std::move(action));
}

void UndoableTable::insertItem(const std::string &string, const size_t position, const bool ignoreErrors) {
	_record(Table::_insertItem(string, position, ignoreErrors));
	//Table::insertItem(string, position, ignoreErrors);
}

void UndoableTable::deleteItem(const size_t item) {
	_record(Table::_deleteItem(item));
}

void UndoableTable::insertColumn(std::vector<std::string> &&fields, const size_t position) {
	_record(Table::_insertColumn(std::move(fields), position));
}

void UndoableTable::deleteColumn(const size_t position) {
	_record(Table::_deleteColumn(position));
}

void UndoableTable::setTitle(std::string &&title, const size_t position) {
	_record(Table::_setTitle(std::move(title), position));
}
#include <iostream>
void UndoableTable::sortItems(std::vector<size_t> &&columns) {
	//_record(Table::_sortItems(std::move(columns)));
	Table::_sortItems(std::move(columns));
	std::cerr << "made it to undoable sort!!!\n";
	//for (int i = 0; i < _items.size(); i++)
		//std::cerr << _items[i] << '\n';
}

void UndoableTable::undo() {
	if (_undoableActions.size() > 0) {
		_redoableActions.push_back(_undoableActions.back()->perform(*this));
		_undoableActions.pop_back();
	}
}

void UndoableTable::redo() {
	if (_redoableActions.size() > 0) {
		_undoableActions.push_back(_redoableActions.back()->perform(*this));
		_redoableActions.pop_back();
	}
}
