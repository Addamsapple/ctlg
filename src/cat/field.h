#ifndef FIELD_H
#define FIELD_H

#include <string>
#include <tuple>
#include <vector>

class Field {
	protected:
		std::string _string;

	public:
		Field(std::string &&string);
		virtual ~Field() = default;

		virtual int compare(const Field &field) const;

		const std::string & string() const;
		const char * c_str() const;
		size_t length() const;
};

//make templated? e.g. so that Number can use same factory, and decimal can use the one with precision handling
class FieldFactory {
	public:
		FieldFactory(std::string);

		virtual Field * create(std::string field) const;
};

using FieldFactoryConstructor = FieldFactory * (*)(std::string);

#endif
