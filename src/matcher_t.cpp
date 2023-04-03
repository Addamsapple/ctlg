template<typename T>
void appendToPattern(Pattern &pattern, T argument) {
	pattern.emplace_back(argument);
}

inline void appendToPattern(Pattern &pattern, const char *string) {
	std::string string_(string);
	for (char character : string_)
		appendToPattern(pattern, character);
}

template<typename T, typename... Ts>
void constructPattern(Pattern &pattern, T argument, Ts... arguments) {
	appendToPattern(pattern, argument);
	constructPattern(pattern, arguments...);
}

template<typename T>
void constructPattern(Pattern &pattern, T argument) {
	appendToPattern(pattern, argument);
}

template<typename... Types>
PatternMatcher::PatternMatcher(Types... arguments) : _matchedTokens(0), _partiallyMatched(false) {
	constructPattern(_pattern, arguments...);
}
