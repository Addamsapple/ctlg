#include "type_matcher.h"

void StringTypeMatcher::add(const std::string &string, StringTypeMatcher::callback creator) {
	_matcher.add(string.begin(), string.end(), creator);
}

std::pair<std::unique_ptr<FieldFactory>, MatchResult> StringTypeMatcher::match(const std::string &string) const noexcept {
	auto match_result = _matcher.match(string.begin(), string.end());
	if (match_result.first)
		return std::make_pair(
				(*match_result.first)(std::string(match_result.second, string.end())),
				MatchResult::FullMatch
		);
	return std::make_pair(nullptr, match_result.second != string.begin() ? MatchResult::PartialMatch : MatchResult::NoMatch);
}
