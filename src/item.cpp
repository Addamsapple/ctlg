#include "item.h"
#include "keys.h"
#include "type_proc.h"

Item::Item(size_t fields) {
	_fields.reserve(fields);
}

Item::Item(std::string &&string, const size_t size) : Item(string.size()) {
	auto strings = splitFields(std::move(string));
	if (size > 0 && strings.size() != size)
		throw std::runtime_error("Invalid item format");
	auto constructor = FieldConstructor<Field>({});
	for (std::string &field : strings)
		_fields.emplace_back(constructor.construct(std::move(field)));
}

Item::Item(std::string &&string, const ItemConstructor &constructor) : Item(constructor.size()) {
	auto strings = splitFields(std::move(string));
	if (strings.size() != constructor.size())
		throw std::runtime_error("Invalid item format");
	try {
		for (size_t field = 0; field < constructor.size(); field++)
			_fields.emplace_back(constructor[field]->construct(std::move(std::move(strings[field]))));
	} catch (const std::runtime_error &error) {
		throw std::runtime_error(std::string(error.what()) + " - field " + std::to_string(size() + 1));
	}
}

Field & Item::operator[](size_t field) {
	return *_fields[field];
}

const Field & Item::operator[](size_t field) const {
	return *_fields[field];
}

FieldIterator Item::begin() {
	return _fields.begin();
}

FieldIterator Item::end() {
	return _fields.end();
}

ConstFieldIterator Item::cbegin() const {
	return _fields.cbegin();
}

ConstFieldIterator Item::cend() const {
	return _fields.cend();
}

size_t Item::size() const {
	return _fields.size();
}

StringVector splitFields(std::string &&fields) {
	std::vector<std::string> result;
	size_t startingPosition = 0;
	size_t endingPosition;
	while ((endingPosition = fields.find(KEY_DELIMITER, startingPosition)) != std::string::npos) {
		result.emplace_back(fields.substr(startingPosition, endingPosition - startingPosition));
		startingPosition = endingPosition + 1;
	}
	result.emplace_back(fields.substr(startingPosition));
	return result;
}

ItemConstructor makeItemConstructor(Item &item) {
	ItemConstructor result;
	result.reserve(item.size());
	FieldConstructorInterface *constructor;
	for (auto iterator = item.cbegin(); iterator != item.cend(); iterator++) {
		typeProcessor.match(iterator->get()->string(), constructor);
		result.push_back(constructor);
	}
	return result;
}
