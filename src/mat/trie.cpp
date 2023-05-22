#include "trie.h"

#include "field.h"
#include "command.h"

template<typename T>
void Trie<T>::add(std::string::const_iterator begin, std::string::const_iterator end, T value) {
	auto node = &_root;
	for (auto iterator = begin; iterator != end; iterator++) {
		auto &nextNode = node->children[*iterator];
		if (!nextNode)
			nextNode = std::make_unique<Node<T>>();
		node = nextNode.get();
	}
	if (begin != end)
		node->value = std::make_unique<T>(std::move(value));
}

template<typename T>
std::pair<const T * const, std::string::const_iterator> StringMatcher<T>::match(std::string::const_iterator begin, std::string::const_iterator end) const {
	const T * matchedValue = nullptr;
	auto matchedIterator = begin;
	auto nextNode = &(this->_root);
	for (auto characterIterator = begin; begin != end; characterIterator++) {
		auto nodeIterator = nextNode->children.find(*characterIterator);
		if (nodeIterator == nextNode->children.end()) break;
		nextNode = nodeIterator->second.get();
		if (nextNode->value.get()) {
			matchedValue = nextNode->value.get();
			matchedIterator = characterIterator + 1;
		}
	}
	return std::make_pair(matchedValue, matchedIterator);
}

template<typename T>
CharacterMatcher<T>::CharacterMatcher() { reset(); }

template<typename T>
std::pair<const T * const, MatchResult> CharacterMatcher<T>::match(char character) {
	auto iterator = _matchedNode->children.find(character);
	if (iterator == _matchedNode->children.end())
		return std::make_pair(_matchedNode->value.get(), MatchResult::NoMatch);
	_matchedNode = iterator->second.get();
	const T * matchedValue = iterator->second.get()->value.get();
	return std::make_pair(matchedValue, matchedValue ? MatchResult::FullMatch : MatchResult::PartialMatch);
}

template<typename T>
void CharacterMatcher<T>::reset() { _matchedNode = &(this->_root); }

//TODO: Include arguments defined elsewhere
template class Trie<std::unique_ptr<FieldFactory> (*)(const std::string &)>;
template class Trie<std::unique_ptr<Command> (*)(std::string &&, std::string &&)>;

//TODO: Const std::string & args
template class StringMatcher<std::unique_ptr<FieldFactory> (*)(const std::string &)>;
template class StringMatcher<std::unique_ptr<Command> (*)(std::string &&, std::string &&)>;
template class CharacterMatcher<std::unique_ptr<Command> (*)(std::string &&, std::string &&)>;
