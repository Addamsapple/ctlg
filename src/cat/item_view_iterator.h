#ifndef ITEM_VIEW_ITERATOR_H
#define ITEM_VIEW_ITERATOR_H

#include "item.h"

class ItemViewIterator {
	private:
		const Item *_item;
		std::vector<size_t>::const_iterator _field;
	public:
		using value_type = Field;
		using reference = const value_type &;
		using difference_type = ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;

		ItemViewIterator(const Item *item, std::vector<size_t>::const_iterator field) noexcept : _item(item), _field(field) {}

		reference operator*() const { return _item->get(*_field); }
		reference operator[](difference_type n) const { return _item->get(_field[n]); }

		auto & operator++() noexcept { _field++; return *this; }
		auto & operator--() noexcept { _field--; return *this; }
		auto & operator+=(difference_type n) noexcept { _field += n; return *this; }
		auto & operator-=(difference_type n) noexcept { _field -= n; return *this; }

		auto operator++(int) noexcept { auto result = *this; ++*this; return result; }
		auto operator--(int) noexcept { auto result = *this; --*this; return result; }

		auto operator+(difference_type n) const noexcept { auto result = *this; return result += n; }
		auto operator-(difference_type n) const noexcept { auto result = *this; return result -= n; }

		difference_type operator-(const ItemViewIterator &iterator) const noexcept { return _field - iterator._field; }

		bool operator!=(const ItemViewIterator &iterator) const noexcept { return _field != iterator._field; }
};

#endif
