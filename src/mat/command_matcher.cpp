#include "command_matcher.h"

#include <cctype>

void StringCommandMatcher::add(std::string string, StringCommandMatcher::callback creator) {
	_matcher.add(string.begin(), string.end(), creator);
}

std::pair<std::unique_ptr<Command>, MatchResult> StringCommandMatcher::match(const std::string &string) const {
	auto iterator = string.begin();
	while (iterator != string.end() && isdigit(*iterator))
		iterator++;
	auto match_result = _matcher.match(iterator, string.end());
	if (match_result.first)
		return std::make_pair(
				(*match_result.first)(std::string(string.begin(), iterator), std::string(match_result.second, string.end())),
				MatchResult::FullMatch
		);
	return std::make_pair(nullptr, match_result.second != string.begin() ? MatchResult::PartialMatch : MatchResult::NoMatch);
}

bool CharacterCommandMatcher::_matchToModifier(char character) {
	if (_modifierFinished)
		return false;
	if (isdigit(character)) {
		_modifier += character;
		return true;
	}
	_modifierFinished = true;
	return false;
}

CharacterCommandMatcher::CharacterCommandMatcher() : _modifierFinished(false) {}

void CharacterCommandMatcher::add(std::string string, CharacterCommandMatcher::callback creator) {
	_matcher.add(string.begin(), string.end(), creator);
}

std::pair<std::unique_ptr<Command>, MatchResult> CharacterCommandMatcher::match(char character) {
	auto result = MatchResult::PartialMatch;
	if (!_matchToModifier(character)) {
		auto match_result = _matcher.match(character);
		if (match_result.first) {
			auto command = (*match_result.first)(std::move(_modifier), "");
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
	_modifier.clear();
	_modifierFinished = false;
}
