#include "keys.h"

class __ItemIterator {
	public:
		//const types???
		using value_type = Field;
		using reference = const Field &;
		using pointer = const Field *;
		using difference_type = ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;
	private:
		const Item *_item;
		std::vector<size_t>::const_iterator _index;
	public:
		__ItemIterator(const Item *item, std::vector<size_t>::const_iterator index) noexcept : _item(item), _index(index) {}

		reference operator*() const { return _item->get(*_index); }
		reference operator[](difference_type n) const { return _item->get(_index[n]); }

		__ItemIterator & operator++() noexcept { _index++; return *this; }
		__ItemIterator & operator--() noexcept { _index--; return *this; }
		__ItemIterator & operator+=(difference_type n) noexcept { _index += n; return *this; }
		__ItemIterator & operator-=(difference_type n) noexcept { _index -= n; return *this; }

		__ItemIterator operator++(int) noexcept { auto result = *this; ++*this; return result; }
		__ItemIterator operator--(int) noexcept { auto result = *this; --*this; return result; }

		__ItemIterator operator+(difference_type n) const noexcept { auto result = *this; return result += n; }
		__ItemIterator operator-(difference_type n) const noexcept { auto result = *this; return result -= n; }

		difference_type operator-(const __ItemIterator &iterator) const noexcept { return _index - iterator._index; }

		bool operator!=(const __ItemIterator &iterator) const noexcept { return _index != iterator._index; }
};

class ItemView {
	private:
		const Item *_item;
		const std::vector<size_t> *_indices;
	public:
		ItemView(const Item *item, const std::vector<size_t> *indices) : _item(item), _indices(indices) {}
		const Field & operator[](size_t index) const { return _item->get((*_indices)[index]); }

		__ItemIterator begin() const { return __ItemIterator(_item, _indices->begin()); }
		__ItemIterator end() const { return __ItemIterator(_item, _indices->end()); }

		size_t size() const noexcept { return _indices->size(); }

};

//TODO: define operator<< for Field
inline std::ostream & operator<<(std::ostream &stream, const ItemView &view) {
	if (view.size() > 0)
		stream << view[0].string();
	for (size_t field = 1; field < view.size(); field++)
		stream << KEY_DELIMITER << view[field].string();
	return stream;
}
