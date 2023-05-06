#include "undoable_table.h"

#include "actions.h"

void UndoableTable::_record(std::unique_ptr<Catalogue::Action> &&action) {
	_redoableActions.clear();
	_undoableActions.push_back(std::move(action));
}

void UndoableTable::insertItem(const std::string &string, const size_t position, const bool ignoreErrors) {
	_record(Catalogue::_insertItem(string, position, ignoreErrors));
}

void UndoableTable::deleteItem(const size_t item) {
	_record(Catalogue::_deleteItem(item));
}

void UndoableTable::insertColumn(std::vector<std::string> &&fields, const size_t position) {
	_record(Catalogue::_insertColumn(std::move(fields), position));
}

void UndoableTable::deleteColumn(const size_t position) {
	_record(Catalogue::_deleteColumn(position));
}

void UndoableTable::setTitle(std::string &&title, const size_t position) {
	_record(Catalogue::_setTitle(std::move(title), position));
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
