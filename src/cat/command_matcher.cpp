#include "command_matcher.h"

#include <cctype>
#include <iostream>//testing
bool CommandMatcher::_addToPrefix(char character) {
	if (!_prefixParsed) {
		if (isdigit(character)) {
			_prefix += character;
			return true;
		}
		if (_prefix.size() == 0)
			_prefix = "1";
		std::cerr << "prefix: " << _prefix << '\n';
		_prefixParsed = true;
	}
	return false;
}

void CommandMatcher::add(const std::string &string, CommandConstructor constructor) {
	_matcher.add(string.begin(), string.end(), constructor);
}

size_t CommandMatcher::match(char character, Command **command) {
	if (!_addToPrefix(character)) {
		auto result = _matcher.match(character);
		if (result == FULL_MATCH_)
			*command = (*_matcher.get())(_prefix, "");
		if (result != PARTIAL_MATCH_)
			reset();
		return result;
	}
	return PARTIAL_MATCH_;
}
#include <iostream>
size_t CommandMatcher::match(const std::string &string, Command **command) {
	auto iterator = string.begin();
	while (iterator != string.end() && _addToPrefix(*iterator))
		iterator++;
	size_t result = _matcher.match(iterator, string.end());
	std::cerr << "result: " << result << '\n';
	if (result < PARTIAL_MATCH_) {
		*command = (*_matcher.get())(_prefix, std::string(iterator + result, string.end()));
		result = FULL_MATCH_;
	}
	reset();
	return result;
}

void CommandMatcher::reset() {
	_matcher.reset();
	_prefix.clear();
	_prefixParsed = false;
}
