#include "trie.h"

#include "field.h"

//TODO: return unique_ptr instead of raw pointer
class StringTypeMatcher {
	protected:
		StringMatcher<FieldFactoryConstructor> _matcher;
	public:
		void add(const std::string &string, FieldFactoryConstructor constructor);

		std::pair<FieldFactory *, int> match(const std::string &string) const;
};
