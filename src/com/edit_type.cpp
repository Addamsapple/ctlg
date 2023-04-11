#include "edit_type.h"
#include "interface.h"
#include "io.h"
#include "navigate.h"

#include "return.h"
#include "render.h"
#include "type_proc.h"

bool EditType::execute(StringVector arguments) {
	_position = startingItemColumn + selectedItemColumn;
	_fields.reserve(catalogue.items());
	setOutput(catalogue.types()[_position]->string());
	while (getInput()) {
		_type = std::make_unique<Field>(ioString.data());
		setReturnCode(0, "");
		FieldConstructorInterface *constructor;
		if (typeProcessor.match(_type->string(), constructor) != FULL_MATCH)
			setReturnCode(1, "");
		else
			_constructor = std::unique_ptr<FieldConstructorInterface>(constructor);
		for (auto item = catalogue.begin(); item != catalogue.end() && returnCode() == 0; item++) {
			_fields.emplace_back(_constructor->construct(std::string((*item)[_position]->string())));
		}
		if (returnCode() == 0) {
			_swap();
			return true;
		}
		_fields.clear();
	}
	return false;
}

void EditType::undo() {
	_swap();
}

void EditType::redo() {
	_swap();
}

void EditType::_swap() {
	catalogue.types()[_position].swap(_type);
	catalogue.fieldConstructor(_position).swap(_constructor);
	for (size_t item = 0; item < _fields.size(); item++)
		catalogue[item][_position].swap(_fields[item]);
}
