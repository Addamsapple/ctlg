#ifndef ACTIONS_H
#define ACTIONS_H

#include "catalogue.h"

#include "item.h"

class Catalogue::Action {
	public:
		virtual ~Action() {}

		virtual std::unique_ptr<Catalogue::Action> perform(Catalogue &catalogue) = 0;
};


class Catalogue::InsertItemAction : public Catalogue::Action {
	protected:
		Item _item;
		size_t _index;
	public:
		InsertItemAction(Item &&item, size_t index);

		virtual std::unique_ptr<Catalogue::Action> perform(Catalogue &catalogue);
};


class Catalogue::InsertColumnAction : public Catalogue::Action {
	protected:
		std::vector<std::unique_ptr<Field>> _fields;
		std::unique_ptr<FieldConstructorInterface> _fieldConstructor;
		size_t _column;
	public:
		InsertColumnAction(std::vector<std::unique_ptr<Field>> &&fields, std::unique_ptr<FieldConstructorInterface> &&fieldConstructor, size_t column);

		virtual std::unique_ptr<Catalogue::Action> perform(Catalogue &catalogue);
};


class Catalogue::DeleteItemAction : public Catalogue::Action {
	protected:
		size_t _item;
	public:
		DeleteItemAction(size_t item);

		virtual std::unique_ptr<Catalogue::Action> perform(Catalogue &catalogue);
};


class Catalogue::DeleteColumnAction : public Catalogue::Action {
	protected:
		size_t _column;
	public:
		DeleteColumnAction(size_t column);

		virtual std::unique_ptr<Catalogue::Action>  perform(Catalogue &catalogue);
};


class Catalogue::SetFieldAction : public Catalogue::Action {
	protected:
		std::unique_ptr<Field> _field;
		size_t _item;
		size_t _column;
	public:
		SetFieldAction(std::unique_ptr<Field> &&field, size_t item, size_t column);

		virtual std::unique_ptr<Catalogue::Action> perform(Catalogue &catalogue);
};

#endif
