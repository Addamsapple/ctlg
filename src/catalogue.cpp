#include <fstream>

#include "catalogue.h"

void Catalogue::load(const std::string &file) {
	_items.clear();
	_itemConstructor.clear();
	std::ifstream itemStream(file);
	std::string item;
	try {
		//if there is a type header
		if (std::getline(itemStream, item)) {
			_typeHeader = Item(std::move(item), 0);
			_itemConstructor = makeItemConstructor(_typeHeader);
			//if there is a item header
			if (std::getline(itemStream, item))
				_titleHeader = Item(std::move(item), fields());
			//while there are items
			while (std::getline(itemStream, item))
				_items.emplace_back(std::move(item), _itemConstructor);
		}
		//change error message stuff
	} catch (const std::runtime_error &error) {
		throw std::runtime_error(std::string(error.what()) + " - item " + std::to_string(items()) + " - \"" + file + '\"');
	}
}
Item & Catalogue::typeHeader() {
	return _typeHeader;
}

const Item & Catalogue::typeHeader() const {
	return _typeHeader;
}

Item & Catalogue::titleHeader() {
	return _titleHeader;
}

const Item & Catalogue::titleHeader() const {
	return _titleHeader;
}

Item & Catalogue::operator[](size_t item) {
	return _items[item];
}

const Item & Catalogue::operator[](size_t item) const {
	return _items[item];
}

ItemIterator Catalogue::begin() {
	return _items.begin();
}

ItemIterator Catalogue::end() {
	return _items.end();
}

ConstItemIterator Catalogue::cbegin() const {
	return _items.cbegin();
}

ConstItemIterator Catalogue::cend() const {
	return _items.cend();
}

size_t Catalogue::items() const {
	return _items.size();
}

size_t Catalogue::fields() const {
	return _typeHeader.size();
}
