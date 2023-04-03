#ifndef NUMBER_H
#define NUMBER_H

#include "field.h"

//look into modifying constructors/reassigners to give appropriate default value when supplied an empty string?
//or just make it default to a valid value if an error occurs when trying to assign to empty string?
template<typename Type>
class Number : public Field {
	protected:
		Type _value;

		static std::string ntostr(const Type value, const int precision);
		static std::string ntostr(const Type value);
	public:
		Number(std::string &&string, const int precision);
		Number(std::string &&string);

		void reassign(std::string &&string, const int precision);
		void reassign(std::string &&string) override;
		
		static Type strton(const std::string &string);

		bool operator<(const Field &field) const override;
};

#include "number_t.cpp"

#endif
