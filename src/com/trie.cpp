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
std::pair<T *, std::string::const_iterator> StringMatcher<T>::match(std::string::const_iterator begin, std::string::const_iterator end) {
	T * matchedVal = nullptr;
	size_t matchedChars = 0;
	auto nextNode = &(this->_root);
	for (auto charIter = begin; begin != end; charIter++) {
		auto nodeIter = nextNode->children.find(*charIter);
		if (nodeIter == nextNode->children.end()) break;
		nextNode = nodeIter->second.get();
		if (nextNode->value.get()) {
			matchedVal = nextNode->value.get();
			matchedChars++;
		}
	}
	return std::make_pair(matchedVal, begin + matchedChars);
}

template<typename T>
CharacterMatcher<T>::CharacterMatcher() { reset(); }

template<typename T>
std::pair<T *, size_t> CharacterMatcher<T>::match(char character) {
	auto nodeIter = _matchedNode->children.find(character);
	if (nodeIter == _matchedNode->children.end())
		return std::make_pair(_matchedNode->value.get(), NO_MATCH_);
	_matchedNode = nodeIter->second.get();
	T * matchedVal = nodeIter->second.get()->value.get();
	return std::make_pair(matchedVal, matchedVal ? FULL_MATCH_ : PARTIAL_MATCH_);
}

template<typename T>
void CharacterMatcher<T>::reset() { _matchedNode = &(this->_root); }

template class Trie<FieldFactory * (*)(std::string)>;
template class Trie<Command * (*)(std::string, std::string)>;

template class StringMatcher<FieldFactory * (*)(std::string)>;
template class StringMatcher<Command * (*)(std::string, std::string)>;
template class CharacterMatcher<Command * (*)(std::string, std::string)>;

//template class Matcher<Command * (*)(std::string, std::string)>;
//template class Matcher<FieldFactory * (*)(std::string)>;
