#ifndef NUMBER_H
#define NUMBER_H

#include "field.h"

//consider moving rounding logic to a decimal class?
template<typename Type>//just use T instead of Type
class Number : public Field {
	protected:
		Type _value;

		static std::string ntostr(const Type value, const int precision);
		static std::string ntostr(const Type value);
	public:
		Number(const std::string &string, const int precision);
		Number(const std::string &string);

		static Type strton(const std::string &string);

		int compare(const Field &field) const override;
};

template<typename T>
class NumberFactory : public FieldFactory {
	protected:
		int _precision;

		std::unique_ptr<Field> (NumberFactory<T>::*_callback)(std::string &&) const;

		std::unique_ptr<Field> _createWithArgs(std::string &&field) const;
		std::unique_ptr<Field> _createWithoutArgs(std::string &&field) const;
	public:
		NumberFactory(const std::string &arguments);

		virtual std::unique_ptr<Field> create(std::string &&number) const override;
};

//#include "number_t.cpp"

#endif
