#ifndef FIELD_H
#define FIELD_H

#include <memory>
#include <string>
#include <tuple>
#include <vector>

class Field {
	protected:
		std::string _string;

	public:
		Field(std::string string);
		virtual ~Field() = default;

		virtual int compare(const Field &field) const;

		const std::string & string() const;
		const char * c_str() const;
		size_t length() const;
};

std::ostream & operator<<(std::ostream &stream, const Field &field);

//TODO: make templated
//TODO: use auto return type
class FieldFactory {
	public:
		FieldFactory(const std::string &args);

		virtual std::unique_ptr<Field> create(std::string &&field) const;
};

//TODO: remove? move?
using FieldFactoryConstructor = FieldFactory * (*)(std::string);

#endif
