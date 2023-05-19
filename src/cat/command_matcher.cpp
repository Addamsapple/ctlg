#include "command_matcher.h"

#include <cctype>

bool CommandMatcher::_addToPrefix(char character) {
	if (!_prefixParsed) {
		if (isdigit(character)) {
			_prefix += character;
			return true;
		}
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

size_t CommandMatcher::match(const std::string &string, Command **command) {
	auto iterator = string.begin();
	while (iterator != string.end() && _addToPrefix(*iterator))
		iterator++;
	auto matched_iterator = _matcher.match(iterator, string.end());
	size_t result = NO_MATCH_;
	if (matched_iterator != iterator) {
		if (!_matcher.get()) result = PARTIAL_MATCH_;
		else {
			*command = (*_matcher.get())(_prefix, std::string(matched_iterator, string.end()));
			result = FULL_MATCH_;
		}
	}
	reset();
	return result;
}

void CommandMatcher::reset() {
	_matcher.reset();
	_prefix.clear();
	_prefixParsed = false;
}
