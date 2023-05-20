#include "type_matcher.h"

void StringTypeMatcher::add(const std::string &string, FieldFactoryConstructor constructor) {
	_matcher.add(string.begin(), string.end(), constructor);
}

/*size_t TypeMatcher::match(const std::string &string, FieldFactory **constructor) {
	auto iterator = string.begin();//remove this line, not necessary?
	auto matched_iterator = _matcher.match(iterator, string.end());
	size_t result = NO_MATCH_;
	if (matched_iterator != iterator) {//compare to begin instead of iterator, which will be removed?
		if (!_matcher.get()) result = PARTIAL_MATCH_;
		else {
			*constructor = (*_matcher.get())(std::string(matched_iterator, string.end()));
			result = FULL_MATCH_;
		}
	}
	_matcher.reset();
	return result;
}*/

std::pair<FieldFactory *, size_t> StringTypeMatcher::match(const std::string &string) {
	auto match_result = _matcher.match(string.begin(), string.end());
	if (match_result.first) {
		FieldFactory *factory = (*match_result.first)(std::string(match_result.second, string.end()));
		return std::make_pair(factory, FULL_MATCH_);
	}
	return std::make_pair(nullptr, match_result.second != string.begin() ? PARTIAL_MATCH_ : NO_MATCH_);
}
