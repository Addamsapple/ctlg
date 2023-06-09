#ifndef TABLE_VIEW_ITERATOR_H
#define TABLE_VIEW_ITERATOR_H

#include "item_view.h"

class TableViewIterator {
	private:
		const Table *_table;
		std::vector<size_t>::const_iterator _item;
		const std::vector<size_t> *_fields;
	public:
		using value_type = ItemView;
		using reference = value_type;
		using difference_type = ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;

		TableViewIterator(const Table *table, std::vector<size_t>::const_iterator item, const std::vector<size_t> *fields) noexcept : _table(table), _item(item), _fields(fields) {}

		reference operator*() const { return ItemView(&((*_table)[*_item]), _fields); }
		reference operator[](difference_type n) const { return ItemView(&((*_table)[_item[n]]), _fields); }

		auto & operator++() noexcept { _item++; return *this; }
		auto & operator--() noexcept { _item--; return *this; }
		auto & operator+=(difference_type n) noexcept { _item += n; return *this; }
		auto & operator-=(difference_type n) noexcept { _item -= n; return *this; }

		auto operator++(int) noexcept { auto result = *this; ++*this; return result; }
		auto operator--(int) noexcept { auto result = *this; --*this; return result; }

		auto operator+(difference_type n) const noexcept{ auto result = *this; return result += n; }
		auto operator-(difference_type n) const noexcept { auto result = *this; return result -= n; }

		difference_type operator-(const TableViewIterator &iterator) const noexcept { return _item - iterator._item; }

		bool operator!=(const TableViewIterator &iterator) const noexcept { return _item != iterator._item; }
		bool operator<(const TableViewIterator &iterator) const noexcept { return _item < iterator._item; }
};

#endif
