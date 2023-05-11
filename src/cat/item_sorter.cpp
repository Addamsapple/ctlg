#include "item_sorter.h"

#include <algorithm>

#include "table.h"
#include "item.h"

template<typename T>
Compare<T>::Compare(std::vector<size_t> &&elements) : _elements(std::move(elements)) {}

template<typename T>
bool Compare<T>::operator()(const T &a, const T &b) {
	for (auto element = _elements.cbegin(); element != _elements.cend(); element++) {
		int comparison = _element(a, *element).compare(_element(b, *element));
		if (comparison < 0)
			return true;
		else if (comparison > 0)
			return false;
	}
	return false;
}

template class Compare<Item>;

template<>
auto Compare<Item>::_element(const Item &item, const int element) {
	return item.get(element);
}

//remove this overload, and just define a helper function inside actions or whereever, say iota() that returns a vector of a specific size with a specific starting value
template<typename T>
std::vector<size_t> sortedOrder(const T &list, Compare<typename T::value_type> &&compare) {
	std::vector<size_t> indices;
	indices.reserve(list.size());
	for (size_t index = 0; index < list.size(); index++)
		indices.push_back(index);
	return sortedOrder(list, indices, std::move(compare));
}

//consider std::sort if performance is not satisfactory, and stability is not a concern
template<typename T>
std::vector<size_t> sortedOrder(const T &list, std::vector<size_t> indices, Compare<typename T::value_type> &&compare) {
	std::stable_sort(indices.begin(), indices.end(),
			[&list, &compare](const size_t &a, const size_t &b){ return compare(list[a], list[b]); });
	return indices;
}

template std::vector<size_t> sortedOrder(const std::vector<Item> &items, Compare<Item> &&compare);
template std::vector<size_t> sortedOrder(const std::vector<Item> &items, std::vector<size_t> indices, Compare<Item> &&compare);
