#include "set_field.h"

#include "interface.h"
#include "populate.h"

bool SetField::execute(StringVector arguments) {
	table.setField(std::move(arguments[0]), itemView.firstElement() + itemView.selectedElement(), itemColumnView.firstElement() + itemColumnView.selectedElement());
	return true;
}

void SetField::undo() { table.undo(); }
void SetField::redo() { table.redo(); }
