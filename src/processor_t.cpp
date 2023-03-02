template<typename T, typename... Ts>
int Processor<T, Ts...>::match(const char character, Ts... arguments) {
	int result = _processor.match(character, true);
	if (result == NO_MATCH)
		reset();
	else if (result > PARTIAL_MATCH) {
		invoke(result, arguments...);
		result = FULL_MATCH;
		reset();
	}
	return result;
}

template<typename T, typename... Ts>
int Processor<T, Ts...>::match(const std::string &string, Ts... arguments) {
	int result = _processor.match(string);
	if (result > PARTIAL_MATCH) {
		invoke(result, arguments...);
		result = FULL_MATCH;
	}
	reset();
	return result;
}

template<typename T, typename... Ts>
void Processor<T, Ts...>::add(T callback, PatternMatcher &&matcher) {
	_callbacks.emplace_back(callback);
	_processor.add(std::move(matcher));
}

template<typename T, typename... Ts>
void Processor<T, Ts...>::reset() {
	_processor.reset();
}
