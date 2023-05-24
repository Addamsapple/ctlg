#include "type_proc.h"

#include "number.h"

template<typename T>
std::unique_ptr<FieldFactory> fieldFactoryConstructor(const std::string &arguments) {
	return std::make_unique<T>(arguments);
}

#define PAIR(string_, type)\
	std::make_pair(std::string(string_), fieldFactoryConstructor<type>)

StringTypeMatcher typeProcessor(
		PAIR("fld", FieldFactory),
		PAIR("num-l", NumberFactory<long>),
		PAIR("num-ul", NumberFactory<size_t>),
		PAIR("num-f", NumberFactory<float>)
);
