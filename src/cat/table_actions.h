#ifndef ACTIONS_H
#define ACTIONS_H

#include "table.h"

#include "item.h"

class Table::Action {
	public:
		virtual ~Action() {}

		virtual std::unique_ptr<Table::Action> perform(Table &table) = 0;
};


//add override keywords
class Table::InsertItemAction : public Table::Action {
	protected:
		Item _item;
		size_t _index;
	public:
		InsertItemAction(Item &&item, size_t index);

		virtual std::unique_ptr<Table::Action> perform(Table &table);
};

class Table::InsertColumnAction : public Table::Action {
	protected:
		std::vector<std::unique_ptr<Field>> _fields;
		std::unique_ptr<FieldFactory> _fieldConstructor;
		size_t _column;
	public:
		InsertColumnAction(std::vector<std::unique_ptr<Field>> &&fields, std::unique_ptr<FieldFactory> &&fieldConstructor, size_t column);

		virtual std::unique_ptr<Table::Action> perform(Table &table);
};

class Table::DeleteItemAction : public Table::Action {
	protected:
		size_t _item;
	public:
		DeleteItemAction(size_t item);

		virtual std::unique_ptr<Table::Action> perform(Table &table);
};

class Table::DeleteColumnAction : public Table::Action {
	protected:
		size_t _column;
	public:
		DeleteColumnAction(size_t column);

		virtual std::unique_ptr<Table::Action>  perform(Table &table);
};

class Table::SetFieldAction : public Table::Action {
	protected:
		std::unique_ptr<Field> _field;
		size_t _item;
		size_t _column;
	public:
		SetFieldAction(std::unique_ptr<Field> &&field, size_t item, size_t column);

		virtual std::unique_ptr<Table::Action> perform(Table &table);
};

class Table::SetTitleAction : public Table::Action {
	protected:
		std::unique_ptr<Field> _title;
		size_t _column;
	public:
		SetTitleAction(std::unique_ptr<Field> &&title, size_t column);

		virtual std::unique_ptr<Table::Action> perform(Table &table);
};

class Table::SetOrderAction : public Table::Action {
	protected:
		std::vector<size_t> _order;
	public:
		SetOrderAction(std::vector<size_t> &&order);

		virtual std::unique_ptr<Table::Action> perform(Table &table);
};

#endif
