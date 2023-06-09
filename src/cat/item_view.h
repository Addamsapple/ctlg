#ifndef ITEM_VIEW_H
#define ITEM_VIEW_H

#include "item_view_iterator.h"
#include "keys.h"

class ItemView {
	private:
		const Item *_item;
		const std::vector<size_t> *_indices;
	public:
		ItemView(const Item *item, const std::vector<size_t> *indices) : _item(item), _indices(indices) {}
		const Field & operator[](size_t index) const { return _item->get((*_indices)[index]); }

		auto begin() const { return ItemViewIterator(_item, _indices->begin()); }
		auto end() const { return ItemViewIterator(_item, _indices->end()); }

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

#endif
