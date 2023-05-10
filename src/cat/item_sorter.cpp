#include "item_sorter.h"

#include <algorithm>

#include "table.h"
#include "item.h"

template<typename T>
Compare<T>::Compare(std::vector<size_t> &&elements) : _elements(std::move(elements)) {}
#include <iostream>
template<typename T>
bool Compare<T>::operator()(const T &a, const T &b) {
	for (auto element = _elements.cbegin(); element != _elements.cend(); element++) {
		int comparison = _element(a, *element).compare(_element(b, *element));
		if (comparison < 0)
			return true;
		else if (comparison > 0)
			return false;
	}
	std::cerr << "compared\n";
	return true;
}

template class Compare<Item>;

template<>
auto Compare<Item>::_element(const Item &item, const int element) {
	return item.get(element);
}
template<typename T>

//remove this overload, and just define a helper function inside actions or whereever, say iota() that returns a vector of a specific size with a specific starting value
std::vector<size_t> sortedOrder(const T &list, Compare<typename T::value_type> &&compare) {
	std::vector<size_t> indices;
	indices.reserve(list.size());
	for (size_t index = 0; index < list.size(); index++)//OOB error, because Table.size() returns size including header elements, which we do not want. options are to separate header into separate member(s), maybe just a vector of items called _header
		indices.push_back(index);
	return sortedOrder(list, indices, std::move(compare));
}

template<typename T>
class Bruh {
	T &_list;
	Compare<typename T::value_type> _compare;
	public:
		Bruh(T &list, Compare<typename T::value_type> &&compare) : _list(list), _compare(std::move(compare)) {}
		int operator()(size_t &a, size_t &b){ return _compare(_list[a], _list[b]); }
};

template<typename T>
std::vector<size_t> sortedOrder(const T &list, std::vector<size_t> indices, Compare<typename T::value_type> &&compare) {
	//std::sort(indices.begin(), indices.end(),
			//[&list, &compare](size_t &a, size_t &b){ return compare(list[a], list[b]); });
	std::sort(indices.begin(), indices.end(), Bruh(list, std::move(compare)));

	std::cerr << "sorting done!!!\n";
	return indices;
}



template std::vector<size_t> sortedOrder(const Table &table, Compare<Item> &&compare);
template std::vector<size_t> sortedOrder(const Table &table, std::vector<size_t> indices, Compare<Item> &&compare);
