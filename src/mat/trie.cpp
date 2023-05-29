#include "trie.h"

#include "field.h"
#include "command.h"

template<typename T>
void Trie<T>::add(std::string::const_iterator begin, std::string::const_iterator end, T value) {
	auto node = &_root;
	for (auto iterator = begin; iterator != end; iterator++)
		node = &(node->children[*iterator]);
	if (begin != end)
		node->value = std::move(value);
}

template<typename T>
std::pair<const T * const, std::string::const_iterator> StringMatcher<T>::match(std::string::const_iterator begin, std::string::const_iterator end) const noexcept {
	const T *matchedValue = nullptr;
	auto matchedIterator = begin;
	auto node = &(this->_root);
	for (auto characterIterator = begin; begin != end; characterIterator++) {
		auto nodeIterator = node->children.find(*characterIterator);
		if (nodeIterator == node->children.end()) break;
		node = &(nodeIterator->second);
		if (node->value) {
			matchedValue = &(node->value.value());
			matchedIterator = characterIterator + 1;
		}
	}
	return std::make_pair(matchedValue, matchedIterator);
}

template<typename T>
CharacterMatcher<T>::CharacterMatcher() { reset(); }

template<typename T>
std::pair<const T * const, MatchResult> CharacterMatcher<T>::match(char character) const noexcept {
	auto iterator = _matchedNode->children.find(character);
	if (iterator == _matchedNode->children.end())
		return std::make_pair(nullptr, MatchResult::NoMatch);
	_matchedNode = &(iterator->second);
	const T *matchedValue = _matchedNode->value ? &(_matchedNode->value.value()) : nullptr;
	return std::make_pair(matchedValue, matchedValue ? MatchResult::FullMatch : MatchResult::PartialMatch);
}

template<typename T>
void CharacterMatcher<T>::reset() const noexcept { _matchedNode = &(this->_root); }

//TODO: Include arguments defined elsewhere
template class Trie<std::unique_ptr<FieldFactory> (*)(const std::string &)>;
template class Trie<std::unique_ptr<Command> (*)(std::string &&, std::string &&)>;

template class StringMatcher<std::unique_ptr<FieldFactory> (*)(const std::string &)>;
template class StringMatcher<std::unique_ptr<Command> (*)(std::string &&, std::string &&)>;
template class CharacterMatcher<std::unique_ptr<Command> (*)(std::string &&, std::string &&)>;
