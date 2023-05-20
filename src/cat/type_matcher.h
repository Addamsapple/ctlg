#include "trie.h"

#include "field.h"

/*class TypeMatcher {
	protected:
		Matcher<FieldFactoryConstructor> _matcher;
	public:
		void add(const std::string &string, FieldFactoryConstructor constructor);
		size_t match(const std::string &string, FieldFactory **constructor);

};*/

class StringTypeMatcher {
	protected:
		StringMatcher<FieldFactoryConstructor> _matcher;
	public:
		void add(const std::string &string, FieldFactoryConstructor constructor);

		std::pair<FieldFactory *, size_t> match(const std::string &string);
};
