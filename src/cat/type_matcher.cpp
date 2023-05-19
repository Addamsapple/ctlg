#include "type_matcher.h"

void TypeMatcher::add(const std::string &string, FieldFactoryConstructor constructor) {
	_matcher.add(string.begin(), string.end(), constructor);
}
size_t TypeMatcher::match(const std::string &string, FieldFactory **constructor) {
	auto iterator = string.begin();
	auto matched_iterator = _matcher.match(iterator, string.end());
	size_t result = NO_MATCH_;
	if (matched_iterator != iterator) {
		if (!_matcher.get()) result = PARTIAL_MATCH_;
		else {
			*constructor = (*_matcher.get())(std::string(matched_iterator, string.end()));
			result = FULL_MATCH_;
		}
	}
	_matcher.reset();
	return result;
}
