#include "type_matcher.h"

void StringTypeMatcher::add(const std::string &string, FieldFactoryConstructor constructor) {
	_matcher.add(string.begin(), string.end(), constructor);
}

std::pair<FieldFactory *, int> StringTypeMatcher::match(const std::string &string) const {
	auto match_result = _matcher.match(string.begin(), string.end());
	if (match_result.first) {
		FieldFactory *factory = (*match_result.first)(std::string(match_result.second, string.end()));
		return std::make_pair(factory, FULL_MATCH_);
	}
	return std::make_pair(nullptr, match_result.second != string.begin() ? PARTIAL_MATCH_ : NO_MATCH_);
}
