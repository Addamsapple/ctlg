#include "field.h"

Field::Field(std::string &&string) : _string(std::move(string)) {}

void Field::reassign(std::string &&string) {
	_string = string;
}

bool Field::operator<(const Field &field) const {
	return _string < field._string;
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
