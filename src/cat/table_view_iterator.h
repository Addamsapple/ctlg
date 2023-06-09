#ifndef TABLE_VIEW_ITERATOR_H
#define TABLE_VIEW_ITERATOR_H

#include "item_view.h"

class TableViewIterator {
	private:
		const Table *_table;
		std::vector<size_t>::const_iterator _index;//TODO: rename
		const std::vector<size_t> *_indices;//TODO: rename
	public:
		using value_type = ItemView;
		using reference = value_type;
		using difference_type = ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;

		TableViewIterator(const Table *table, std::vector<size_t>::const_iterator index, const std::vector<size_t> *indices) noexcept : _table(table), _index(index), _indices(indices) {}

		reference operator*() const { return ItemView(&((*_table)[*_index]), _indices); }
		reference operator[](difference_type n) const { return ItemView(&((*_table)[_index[n]]), _indices); }

		auto & operator++() noexcept { _index++; return *this; }
		auto & operator--() noexcept { _index--; return *this; }
		auto & operator+=(difference_type n) noexcept { _index += n; return *this; }
		auto & operator-=(difference_type n) noexcept { _index -= n; return *this; }

		auto operator++(int) noexcept { auto result = *this; ++*this; return result; }
		auto operator--(int) noexcept { auto result = *this; --*this; return result; }

		auto operator+(difference_type n) const noexcept{ auto result = *this; return result += n; }
		auto operator-(difference_type n) const noexcept { auto result = *this; return result -= n; }

		difference_type operator-(const TableViewIterator &iterator) const noexcept { return _index - iterator._index; }

		bool operator!=(const TableViewIterator &iterator) const noexcept { return _index != iterator._index; }
		bool operator<(const TableViewIterator &iterator) const noexcept { return _index < iterator._index; }
};

#endif
