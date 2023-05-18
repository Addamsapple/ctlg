#include "command_matcher.h"

#include <cctype>

bool CommandMatcher::_addToPrefix(char character) {
	if (!_prefixParsed) {
		if (isdigit(character)) {
			_prefix += character;
			return true;
		}
		if (_prefix.size() == 0)
			_prefix = "1";
		_prefixParsed = true;
	}
	return false;
}

void CommandMatcher::add(const std::string &string, CommandConstructor constructor) {
	_matcher.add(string, constructor);
}

int CommandMatcher::match(char character, Command **command) {
	if (!_addToPrefix(character)) {
		auto result = _matcher.match(character);
		if (result == FULL_MATCH)
			*command = (*_matcher.get())({});
		if (result != PARTIAL_MATCH)
			reset();
		return result;
	}
	return PARTIAL_MATCH;
}

int CommandMatcher::match(const std::string &string, Command **) {
	auto character = string.begin();
	while (character != string.end() && _addToPrefix(*character))
		character++;
	_matcher.match(iterator, string.end());
	//check return value, and decide what to do from there.
}

void CommandMatcher::reset() {
	_matcher.reset();
	_prefix.clear();
}
