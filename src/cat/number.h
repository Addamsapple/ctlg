#ifndef NUMBER_H
#define NUMBER_H

#include "field.h"

//consider moving rounding logic to a decimal class?
template<typename Type>
class Number : public Field {
	protected:
		Type _value;

		static std::string ntostr(const Type value, const int precision);
		static std::string ntostr(const Type value);
	public:
		Number(const std::string &string, const int precision);
		Number(const std::string &string);

		static Type strton(const std::string &string);

		bool operator<(const Field &field) const override;
};

#include "number_t.cpp"

#endif
