#ifndef MATCHER_H
#define MATCHER_H

#include <string>
#include <vector>

#include "token.h"

using StringVector = std::vector<std::string>;
using Pattern = std::vector<Token>;

class PatternMatcher {
	protected:
		Pattern _pattern;

		size_t _matchedTokens;
		bool _partiallyMatched;//rename?
		StringVector _arguments;
	public:
		template<typename... Types> PatternMatcher(Types... arguments);

		bool match(const char character);
		bool match() const;

		void reset();

		StringVector & arguments();
};

#include "matcher_t.cpp"

#endif
