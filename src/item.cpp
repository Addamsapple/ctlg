#include "item.h"
#include "keys.h"
#include "type_proc.h"
#include "return.h"

Item::Item(size_t fields) {
	_fields.reserve(fields);
}

Item::Item(StringVector &&item, const ItemConstructor &constructor) : Item(constructor.size()) {
	size_t returnCode_ = 0;
	std::string returnMessage_;
	if (item.size() < constructor.size()) {
		while (item.size() < constructor.size())
			item.push_back("");
		returnCode_ = ITEM_TOO_FEW_FIELDS_ERROR;
		returnMessage_ = "too few fields";
	} else if (item.size() > constructor.size()) {
		item.erase(item.begin() + constructor.size(), item.end());//confirm that this works
		returnCode_ = ITEM_TOO_MANY_FIELDS_ERROR;
		returnMessage_ = "too many fields";
	}
	for (size_t field = 0; field < constructor.size(); field++) {
		_fields.emplace_back(constructor[field]->construct(std::move(std::move(item[field]))));
		if (returnCode() != 0) {
			returnMessage_ += "|f" + std::to_string(field) + ":" + returnMessage();
			returnCode_ = std::max(returnCode_, returnCode());
		}
	}
	setReturnCode(returnCode_, returnMessage_);
}

Item::Item(StringVector &&item, const size_t fields) : Item(fields) {
	setReturnCode(0, "");
	if (fields > 0) {
		if (item.size() < fields) {
			while (item.size() < fields)
				item.push_back("");
			setReturnCode(ITEM_TOO_FEW_FIELDS_ERROR, "too few fields");
		} else if (item.size() > fields)
			setReturnCode(ITEM_TOO_MANY_FIELDS_ERROR, "too many fields");
	}
	auto constructor = FieldConstructor<Field>({});
	for (std::string &field : item)
		_fields.emplace_back(constructor.construct(std::move(field)));
}

Item::Item(StringVector &&item) : Item(std::move(item), 0) {}

Item::Item(const std::string &string, const ItemConstructor &constructor) : Item(splitItem(string), constructor) {}
Item::Item(const std::string &string, const size_t fields) : Item(splitItem(string), fields) {}
Item::Item(const std::string &string) : Item(splitItem(string)) {}

void Item::insertField(std::string &&string, const FieldConstructorInterface &constructor, const size_t position) {
	_fields.insert(_fields.begin() + position, std::unique_ptr<Field>(constructor.construct(std::move(string))));
	//move uptr?
}

void Item::deleteField(const size_t position) {
	_fields.erase(begin() + position);
}

std::unique_ptr<Field> & Item::operator[](size_t field) {
	return _fields[field];
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

void Item::clear() {
	_fields.clear();
}

std::string repeatField(const std::string &string, const size_t fields) {
	std::string result;
	size_t fields_ = std::max(fields, (std::size_t) 1);
	result.reserve((string.size() + 1) * fields_ - 1);
	result += string;
	for (size_t field = 1; field < fields_; field++)
		result += KEY_DELIMITER + string;
	return result;
}

//shouldn't this be called splitItem()?
StringVector splitItem(const std::string &item) {
	StringVector result;
	size_t start = 0;
	size_t end;
	while ((end = item.find(KEY_DELIMITER, start)) != std::string::npos) {
		result.emplace_back(item.substr(start, end - start));
		start = end + 1;
	}
	result.emplace_back(item.substr(start));
	return result;
}

ItemConstructor makeItemConstructor(const Item &item) {
	ItemConstructor result;
	result.reserve(item.size());
	FieldConstructorInterface *constructor;
	//rename variable to type?/field?
	for (auto iterator = item.cbegin(); iterator != item.cend(); iterator++)
		if (typeProcessor.match(iterator->get()->string(), constructor) == FULL_MATCH)
			result.push_back(constructor);
		else {
			setReturnCode(ITEM_CONSTRUCTOR_TYPE_ERROR, "type mismatch");
			break;
		}
	return result;
}

ItemConstructor makeItemConstructor(const size_t fields) {
	ItemConstructor result;
	for (size_t field = 0; field < fields; field++)
		result.push_back(new FieldConstructor<Field>({}));
	return result;
}
