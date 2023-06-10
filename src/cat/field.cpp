#include "field.h"

Field::Field(std::string string) : _string(std::move(string)) {}

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

std::ostream & operator<<(std::ostream &stream, const Field &field) { return stream << field.string(); }

FieldFactory::FieldFactory(const std::string &args) {}

std::unique_ptr<Field> FieldFactory::create(std::string &&field) const {
	return std::make_unique<Field>(std::move(field));
}
