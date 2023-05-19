#include "number.h"
#include "type_proc.h"

/*template<typename T, typename... Ts>
FieldConstructorInterface * fieldConstructorConstructor(StringVector &&arguments) {
	return new FieldConstructor<T, Ts...>(std::move(arguments));
}*/

template<typename T>
FieldFactory * fieldFactoryConstructor(std::string arguments) {
	return new T(std::move(arguments));
}

//#define ADD_TYPE_RULE(constructor, ...)
#define ADD_TYPE_RULE(string, command)\
	typeProcessor.add(string, CONSTRUCTOR(command))
	//typeProcessor.add(constructor, PatternMatcher(__VA_ARGS__))

#define CONSTRUCTOR(...)\
	fieldFactoryConstructor<__VA_ARGS__>

void loadTypes() {
	ADD_TYPE_RULE("fld", FieldFactory);
	ADD_TYPE_RULE("num-l", NumberFactory<long>);
	ADD_TYPE_RULE("num-ul", NumberFactory<size_t>);
	ADD_TYPE_RULE("num-f", NumberFactory<float>);
	/*ADD_TYPE_RULE(CONSTRUCTOR(Field), "fld");
	ADD_TYPE_RULE(CONSTRUCTOR(Number<long>), "num-l");
	ADD_TYPE_RULE(CONSTRUCTOR(Number<long long>), "num-ll");
	ADD_TYPE_RULE(CONSTRUCTOR(Number<unsigned long>), "num-ul");
	ADD_TYPE_RULE(CONSTRUCTOR(Number<unsigned long long>), "num-ull");
	ADD_TYPE_RULE(CONSTRUCTOR(Number<float>), "num-f");
	ADD_TYPE_RULE(CONSTRUCTOR(Number<float>, int), "num-f", NUM_TOKEN);
	ADD_TYPE_RULE(CONSTRUCTOR(Number<double>), "num-d");
	ADD_TYPE_RULE(CONSTRUCTOR(Number<double>, int), "num-d", NUM_TOKEN);*/

	//typeProcessor.reset();
}
