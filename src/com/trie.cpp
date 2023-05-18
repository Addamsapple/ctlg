#include "trie.h"

template<typename T>
Matcher<T>::Matcher() { reset(); }

template<typename T>
void Matcher<T>::add(const std::string &string, T value) {
	auto node = &_trie;
	for (size_t character = 0; character < string.size(); character++) {
		auto &nextNode = node->children[string[character]];
		if (!nextNode)
			nextNode = std::make_unique<Node<T>>();
		node = nextNode.get();
	}
	if (string.size() > 0)
		node->value = std::make_unique<T>(std::move(value));
}

template<typename T>
int Matcher<T>::match(char character) {
	if (_node == nullptr) return NO_MATCH;
	auto nextNode = _node->children.find(character);
	if (nextNode == _node->children.end()) return NO_MATCH;
	_node = &(*nextNode->second);
	if (_node->value) return FULL_MATCH;
	return PARTIAL_MATCH;
}

template<typename T>
int Matcher<T>::match(const std::string &string) {
	Node<T> *node = nullptr;
	_node = &_trie;
	for (size_t character = 0; character < string.size(); character++) {
		int matched = match(string[character]);
		if (matched == NO_MATCH) break;
		if (matched == FULL_MATCH) node = _node;
	}
	if (node == nullptr) return NO_MATCH;
	_node = node;
	return FULL_MATCH;
}

template<typename T>
T * Matcher<T>::get() { return _node->value.get(); }

template<typename T>
void Matcher<T>::reset() { _node = &_trie; }

template class Matcher<int>;
