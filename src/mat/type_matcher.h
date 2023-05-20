#include "trie.h"

#include "field.h"

class StringTypeMatcher {
	protected:
		StringMatcher<FieldFactoryConstructor> _matcher;
	public:
		void add(const std::string &string, FieldFactoryConstructor constructor);

		std::pair<FieldFactory *, int> match(const std::string &string) const;
};
