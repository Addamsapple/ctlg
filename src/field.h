#ifndef FIELD_H
#define FIELD_H

#include <string>
#include <tuple>
#include <vector>

//give it a copy method?
class Field {
	protected:
		std::string _string;

	public:
		explicit Field(std::string &&string);

		virtual void reassign(std::string &&string);

		virtual bool operator<(const Field &field) const;

		const std::string & string() const;
		const char * c_str() const;
		size_t length() const;
};

class FieldConstructorInterface {
	public:
		virtual Field * construct(std::string &&string) = 0;
		virtual void reassign(Field *field, std::string &&string) = 0;
};

using StringVector = std::vector<std::string>;

template<typename T, typename... Ts>
class FieldConstructor : public FieldConstructorInterface {
	protected:
		std::tuple<Ts...> _arguments;
	public:
		FieldConstructor(StringVector &&arguments);

		Field * construct(std::string &&string) override;
		void reassign(Field *field, std::string &&string) override;
};

#include "field_t.cpp"

#endif
