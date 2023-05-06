#ifndef ACTIONS_H
#define ACTIONS_H

class Catalogue;

#include "item.h"

//give private constructors
class Action {
	public:
		virtual ~Action() {}

		virtual std::unique_ptr<Action> delegate(Catalogue &catalogue) = 0;
};

class InsertItemAction : public Action {
	friend class Catalogue;
	protected:
		Item _item;
		size_t _index;

		InsertItemAction(Item &&item, size_t index);
	public:
		virtual std::unique_ptr<Action> delegate(Catalogue &catalogue);
};

class InsertColumnAction : public Action {
	friend class Catalogue;
	protected:
		std::vector<std::unique_ptr<Field>> _fields;
		std::unique_ptr<FieldConstructorInterface> _fieldConstructor;

		size_t _column;

		InsertColumnAction(std::vector<std::unique_ptr<Field>> &&fields, std::unique_ptr<FieldConstructorInterface> &&fieldConstructor, size_t column);
	public:
		virtual std::unique_ptr<Action> delegate(Catalogue &catalogue);
};

class DeleteItemAction : public Action {
	friend class Catalogue;
	protected:
		size_t _item;

		DeleteItemAction(size_t item);
	public:
		virtual std::unique_ptr<Action> delegate(Catalogue &catalogue);
};

class DeleteColumnAction : public Action {
	friend class Catalogue;
	protected:
		size_t _column;

		DeleteColumnAction(size_t column);
	public:
		virtual std::unique_ptr<Action>  delegate(Catalogue &catalogue);
};

class SetFieldAction : public Action {
	friend class Catalogue;
	protected:
		std::unique_ptr<Field> _field;

		size_t _item;
		size_t _column;

		SetFieldAction(std::unique_ptr<Field> &&field, size_t item, size_t column);
	public:
		virtual std::unique_ptr<Action> delegate(Catalogue &catalogue);
};

#endif
