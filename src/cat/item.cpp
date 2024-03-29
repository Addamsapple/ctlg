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
		_fields.emplace_back(constructor[field]->create(std::move(std::move(item[field]))));
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
	for (std::string &field : item)
		_fields.push_back(std::make_unique<Field>(std::move(field)));
}

Item::Item(StringVector &&item) : Item(std::move(item), 0) {}

Item::Item(const std::string &string, const ItemConstructor &constructor) : Item(splitItem(string), constructor) {}
Item::Item(const std::string &string, const size_t fields) : Item(splitItem(string), fields) {}
Item::Item(const std::string &string) : Item(splitItem(string)) {}

void Item::insertField(std::string &&string, const FieldFactory &constructor, const size_t position) { _fields.insert(_fields.begin() + position, std::unique_ptr<Field>(constructor.create(std::move(string)))); }

void Item::insertField(std::string &&string, const size_t position) {
	_fields.insert(_fields.begin() + position, std::make_unique<Field>(std::move(string)));
}

void Item::insertField(std::unique_ptr<Field> &&field, const size_t position) { _fields.insert(_fields.begin() + position, std::move(field)); }

void Item::deleteField(const size_t position) { _fields.erase(begin() + position); }

std::unique_ptr<Field> & Item::operator[](size_t field) { return _fields[field]; }
const Field & Item::get(size_t field) const { return *_fields[field]; }

FieldIterator Item::begin() { return _fields.begin(); }
FieldIterator Item::end() { return _fields.end(); }
ConstFieldIterator Item::cbegin() const { return _fields.cbegin(); }
ConstFieldIterator Item::cend() const { return _fields.cend(); }

size_t Item::size() const {
	return _fields.size();
}

void Item::clear() {
	_fields.clear();
}

std::ostream & operator<<(std::ostream &stream, const Item &item) {
	if (item.size() > 0)
		stream << item.get(0).string();
	for (size_t field = 1; field < item.size(); field++)
		stream << KEY_DELIMITER << item.get(field).string();
	return stream;
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
