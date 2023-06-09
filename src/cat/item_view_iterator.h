#ifndef ITEM_VIEW_ITERATOR_H
#define ITEM_VIEW_ITERATOR_H

#include "item.h"

class ItemViewIterator {
	private:
		const Item *_item;
		std::vector<size_t>::const_iterator _index;//TODO: rename
	public:
		using value_type = Field;
		using reference = const value_type &;
		using difference_type = ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;

		ItemViewIterator(const Item *item, std::vector<size_t>::const_iterator index) noexcept : _item(item), _index(index) {}

		const reference operator*() const { return _item->get(*_index); }
		const reference operator[](difference_type n) const { return _item->get(_index[n]); }

		auto & operator++() noexcept { _index++; return *this; }
		auto & operator--() noexcept { _index--; return *this; }
		auto & operator+=(difference_type n) noexcept { _index += n; return *this; }
		auto & operator-=(difference_type n) noexcept { _index -= n; return *this; }

		auto operator++(int) noexcept { auto result = *this; ++*this; return result; }
		auto operator--(int) noexcept { auto result = *this; --*this; return result; }

		auto operator+(difference_type n) const noexcept { auto result = *this; return result += n; }
		auto operator-(difference_type n) const noexcept { auto result = *this; return result -= n; }

		difference_type operator-(const ItemViewIterator &iterator) const noexcept { return _index - iterator._index; }

		bool operator!=(const ItemViewIterator &iterator) const noexcept { return _index != iterator._index; }
};

#endif
