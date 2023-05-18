#include "set_field.h"

#include "interface.h"
#include "populate.h"

SetField::SetField(std::vector<std::string> args) : _field(std::move(args[0])) {}
bool SetField::execute() {
	//table.setField(std::move(arguments[0]), itemView.firstElement() + itemView.selectedElement(), itemColumnView.firstElement() + itemColumnView.selectedElement());
	table.setField(std::move(_field), itemView.firstElement() + itemView.selectedElement(), itemColumnView.firstElement() + itemColumnView.selectedElement());
	return true;
}

void SetField::undo() { table.undo(); }
void SetField::redo() { table.redo(); }
