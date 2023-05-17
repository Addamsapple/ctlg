#ifndef FIELD_CONSTRUCTOR_H
#define FIELD_CONSTRUCTOR_H

#include "field.h"

//virtual destructor?
class FieldConstructorInterface {
	public:
		virtual Field * construct(std::string &&string) const = 0;
};

using StringVector = std::vector<std::string>;

template<typename T, typename... Ts>
class FieldConstructor : public FieldConstructorInterface {
	protected:
		std::tuple<Ts...> _arguments;
	public:
		FieldConstructor(StringVector &&arguments);

		//consider making this return a unique_ptr
		Field * construct(std::string &&string) const override;
};

#include "field_constructor_t.cpp"

#endif
