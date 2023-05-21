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

void StringCommandMatcher::add(std::string string, StringCommandMatcher::callback creator) {
	_matcher.add(string.begin(), string.end(), creator);
}

std::pair<std::unique_ptr<Command>, MatchResult> StringCommandMatcher::match(const std::string &string) const {
	DigitExtractor extractor;
	auto iterator = string.begin();
	while (iterator != string.end() && extractor.match(*iterator))
		iterator++;
	auto match_result = _matcher.match(iterator, string.end());
	if (match_result.first) {
		auto command = (*match_result.first)(extractor.digits(), std::string(match_result.second, string.end()));
		return std::make_pair(std::move(command), MatchResult::FullMatch);
	}
	return std::make_pair(nullptr, match_result.second != string.begin() ? MatchResult::PartialMatch : MatchResult::NoMatch);
}

void CharacterCommandMatcher::add(std::string string, CharacterCommandMatcher::callback creator) {
	_matcher.add(string.begin(), string.end(), creator);
}

std::pair<std::unique_ptr<Command>, MatchResult> CharacterCommandMatcher::match(char character) {
	auto result = MatchResult::PartialMatch;
	if (!_extractor.match(character)) {
		auto match_result = _matcher.match(character);
		if (match_result.first) {
			auto command = (*match_result.first)(_extractor.digits(), "");
			reset();
			return std::make_pair(std::move(command), MatchResult::FullMatch);
		}
		result = match_result.second;
		if (result == MatchResult::NoMatch)
			reset();
	}
	return std::make_pair(nullptr, result);
}

void CharacterCommandMatcher::reset() {
	_matcher.reset();
	_extractor.reset();
}
