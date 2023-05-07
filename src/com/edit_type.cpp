#include "edit_type.h"
#include "interface.h"
#include "io.h"
#include "populate.h"

#include "return.h"
#include "render.h"
#include "type_proc.h"

bool EditType::execute(StringVector arguments) {
/*	_position = itemColumnView.firstElement() + itemColumnView.selectedElement();
	_fields.reserve(table.items());
	setOutput(table.types()[_position]->string());
	while (getInput()) {
		_type = std::make_unique<Field>(ioString.data());
		setReturnCode(0, "");
		FieldConstructorInterface *constructor;
		if (typeProcessor.match(_type->string(), constructor) != FULL_MATCH)
			setReturnCode(1, "");
		else
			_constructor = std::unique_ptr<FieldConstructorInterface>(constructor);
		for (auto item = table.begin(); item != table.end() && returnCode() == 0; item++) {
			_fields.emplace_back(_constructor->construct(std::string((*item)[_position]->string())));
		}

		if (returnCode() == 0) {
			_swap();
			return true;
		}
		_fields.clear();
	}*/
	return false;
}

void EditType::undo() {
	_swap();
}

void EditType::redo() {
	_swap();
}

void EditType::_swap() {
	/*table.types()[_position].swap(_type);
	table.fieldConstructor(_position).swap(_constructor);
	for (size_t item = 0; item < _fields.size(); item++)
		table[item][_position].swap(_fields[item]);*/
}
