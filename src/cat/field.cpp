#include "field.h"

Field::Field(std::string &&string) : _string(std::move(string)) {}

int Field::compare(const Field &field) const {
	return (_string > field._string) - (_string < field._string);
}

const std::string & Field::string() const {
	return _string;
}

const char * Field::c_str() const {
	return _string.c_str();
}

size_t Field::length() const {
	return _string.length();
}

FieldFactory::FieldFactory(std::string) {}

Field * FieldFactory::create(std::string field) const {
	return new Field(std::move(field));
}
