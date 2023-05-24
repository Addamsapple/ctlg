#ifndef TYPE_MATCHER_H
#define TYPE_MATCHER_H

#include "trie.h"

#include "field.h"

class StringTypeMatcher {
	protected:
		using callback = std::unique_ptr<FieldFactory> (*)(const std::string &);

		StringMatcher<callback> _matcher;
	public:
		template<typename... Ts> StringTypeMatcher(Ts... arguments) {
			(add(arguments.first, arguments.second), ...);
		}

		void add(const std::string &string, callback creator);

		std::pair<std::unique_ptr<FieldFactory>, MatchResult> match(const std::string &string) const noexcept;
};

#endif
