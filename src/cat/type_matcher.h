#include "trie.h"

//#include "field_constructor.h"
//using FieldConstructorConstructor = FieldConstructorInterface* (*)(StringVector &&);

#include "field.h"

class TypeMatcher {
	protected:
		Matcher<FieldFactoryConstructor> _matcher;
	public:
		void add(const std::string &string, FieldFactoryConstructor constructor);
		size_t match(const std::string &string, FieldFactory **constructor);

};
