#include "command_matcher.h"

#include <cctype>
/*class StringMatcher {
	
}*/

//CharCommandMatcher: prefix handling and char matching
//StringCommandMatcher: prefix handling and string matching
//TypeMatcher: string matching
//


/*bool CommandMatcher::_addToPrefix(char character) {
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
}*/

DigitExtractor::DigitExtractor() : _finished(false) {}
#include <cctype>
bool DigitExtractor::match(char character) {
	if (!_finished) {
		if (isdigit(character)) {
			_digits += character;
			return true;
		}
		_finished = true;
	}
	return false;
}

const std::string & DigitExtractor::digits() const { return _digits; }

void DigitExtractor::reset() {
	_digits.clear();
	_finished = false;
}

void StringCommandMatcher::add(std::string pattern, CommandConstructor constructor) {
	_matcher.add(pattern.begin(), pattern.end(), constructor);
}

std::pair<Command *, size_t> StringCommandMatcher::match(const std::string &pattern) {
	_extractor.reset();
	auto iterator = pattern.begin();
	while (iterator != pattern.end() && _extractor.match(*iterator))
		iterator++;
	auto match_result = _matcher.match(iterator, pattern.end());
	if (match_result.first) {
		Command *command = (*match_result.first)(_extractor.digits(), std::string(match_result.second, pattern.end()));
		return std::make_pair(command, FULL_MATCH_);
	}
	return std::make_pair(nullptr, match_result.second != iterator ? PARTIAL_MATCH_ : NO_MATCH_);
	//compare match_result.second to pattern.begin() instead? so that strings containing only digits give PARTIAL_MATCH_?
}

void CharacterCommandMatcher::add(std::string pattern, CommandConstructor constructor) {
	_matcher.add(pattern.begin(), pattern.end(), constructor);
}

std::pair<Command *, size_t> CharacterCommandMatcher::match(char character) {
	size_t status = PARTIAL_MATCH_;
	if (!_extractor.match(character)) {
		auto match_result = _matcher.match(character);
		if (match_result.first) {
			Command *command = (*match_result.first)(_extractor.digits(), "");
			_matcher.reset();
			_extractor.reset();
			return std::make_pair(command, FULL_MATCH_);
		}
		status = match_result.second;
		if (status == NO_MATCH_)
			reset();
	}
	return std::make_pair(nullptr, status);
}

void CharacterCommandMatcher::reset() {
	_matcher.reset();
	_extractor.reset();
}
