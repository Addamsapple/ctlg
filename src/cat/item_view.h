#ifndef ITEM_VIEW_H
#define ITEM_VIEW_H

#include "item_view_iterator.h"
#include "keys.h"

class ItemView {
	private:
		const Item *_item;
		const std::vector<size_t> *_fields;
	public:
		ItemView(const Item *item, const std::vector<size_t> *fields) noexcept : _item(item), _fields(fields) {}
		const Field & operator[](size_t index) const { return _item->get((*_fields)[index]); }

		auto begin() const { return ItemViewIterator(_item, _fields->begin()); }
		auto end() const { return ItemViewIterator(_item, _fields->end()); }

		size_t size() const { return _fields->size(); }
};

inline std::ostream & operator<<(std::ostream &stream, const ItemView &view) {
	if (view.size() > 0)
		stream << view[0];
	for (size_t field = 1; field < view.size(); field++)
		stream << KEY_DELIMITER << view[field];
	return stream;
}

#endif
