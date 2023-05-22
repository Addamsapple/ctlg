#include "type_proc.h"

#include "number.h"

template<typename T>
std::unique_ptr<FieldFactory> fieldFactoryConstructor(const std::string &arguments) {
	return std::make_unique<T>(arguments);
}

#define ADD_TYPE_RULE(string, command)\
	typeProcessor.add(string, CONSTRUCTOR(command))

#define CONSTRUCTOR(...)\
	fieldFactoryConstructor<__VA_ARGS__>

void loadTypes() {
	ADD_TYPE_RULE("fld", FieldFactory);
	ADD_TYPE_RULE("num-l", NumberFactory<long>);
	ADD_TYPE_RULE("num-ul", NumberFactory<size_t>);
	ADD_TYPE_RULE("num-f", NumberFactory<float>);
}
