#ifndef TYPE_MATCHER_H
#define TYPE_MATCHER_H

#include "trie.h"

#include "field.h"

class StringTypeMatcher {
	protected:
		using callback = std::unique_ptr<FieldFactory> (*)(std::string);

		StringMatcher<callback> _matcher;
	public:
		void add(const std::string &string, callback creator);

		std::pair<std::unique_ptr<FieldFactory>, MatchResult> match(const std::string &string) const;
};

#endif
