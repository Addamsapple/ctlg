#include "actions.h"

#include "catalogue.h"

InsertItemAction::InsertItemAction(Item &&item, size_t index) :
		_item(std::move(item)),
		_index(index) {}

std::unique_ptr<Action> InsertItemAction::delegate(Catalogue &catalogue) { return catalogue.process(std::move(*this)); }


InsertColumnAction::InsertColumnAction(std::vector<std::unique_ptr<Field>> &&fields, std::unique_ptr<FieldConstructorInterface> &&fieldConstructor, size_t column) :
		_fields(std::move(fields)),
		_fieldConstructor(std::move(fieldConstructor)),
		_column(column) {}

std::unique_ptr<Action> InsertColumnAction::delegate(Catalogue &catalogue) { return catalogue.process(std::move(*this)); }


DeleteItemAction::DeleteItemAction(size_t item) :
		_item(item) {}

std::unique_ptr<Action> DeleteItemAction::delegate(Catalogue &catalogue) { return catalogue.process(std::move(*this)); }


DeleteColumnAction::DeleteColumnAction(size_t column) :
		_column(column) {}

std::unique_ptr<Action> DeleteColumnAction::delegate(Catalogue &catalogue) { return catalogue.process(std::move(*this)); }


SetFieldAction::SetFieldAction(std::unique_ptr<Field> &&field, size_t item, size_t column) :
		_field(std::move(field)),
		_item(item),
		_column(column) {}

std::unique_ptr<Action> SetFieldAction::delegate(Catalogue &catalogue) { return catalogue.process(std::move(*this)); }
