#include "command_matcher.h"

#include <cctype>

DigitExtractor::DigitExtractor() : _finished(false) {}

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
