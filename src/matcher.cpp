#include "matcher.h"

bool PatternMatcher::match(const char character) {
	if (_matchedTokens < _pattern.size()) {
		Token token = _pattern[_matchedTokens];
		bool match_ = token.match(character);
		if (match_) {
			if (_partiallyMatched)
				_arguments.back() += character;
			//change to (token.type() != CHR_TOKEN)
			else if (token.type() == NUM_TOKEN || token.type() == STR_TOKEN) {
				_partiallyMatched = true;
				_arguments.emplace_back(1, character);
			} else
				_matchedTokens++;
			return true;
		} else if (_partiallyMatched) {
			_partiallyMatched = false;
			_matchedTokens++;
			return match(character);
		}
	}
	return false;
}

bool PatternMatcher::match() const {
	return (_matchedTokens == _pattern.size() - 1 && _partiallyMatched) || _matchedTokens == _pattern.size();
}

void PatternMatcher::reset() {
	_matchedTokens = 0;
	_partiallyMatched = false;
	_arguments.clear();
}

StringVector & PatternMatcher::arguments() {
	return _arguments;
}
