#include "table_view.h"

class TableView::Action {
	public:
		virtual ~Action() {}
		
		virtual std::unique_ptr<TableView::Action> perform(TableView &view) = 0;
};

class TableView::InsertItemAction : public TableView::Action {
	private:
		size_t _item;
		size_t _value;
	public:
		InsertItemAction(size_t item, size_t value);

		virtual std::unique_ptr<TableView::Action> perform(TableView &view) override;
};

class TableView::DeleteItemAction : public TableView::Action {
	private:
		size_t _item;
	public:
		DeleteItemAction(size_t item);

		virtual std::unique_ptr<TableView::Action> perform(TableView &view) override;
};

class TableView::InsertColumnAction : public TableView::Action {
	private:
		size_t _column;
		size_t _value;
	public:
		InsertColumnAction(size_t column, size_t value);

		virtual std::unique_ptr<TableView::Action> perform(TableView &view) override;
};

class TableView::DeleteColumnAction : public TableView::Action {
	private:
		size_t _column;
	public:
		DeleteColumnAction(size_t column);

		virtual std::unique_ptr<TableView::Action> perform(TableView &view) override;
};
