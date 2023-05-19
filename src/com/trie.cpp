#include "trie.h"

#include "field.h"
#include "command.h"

template<typename T>
Matcher<T>::Matcher() { reset(); }

template<typename T>
void Matcher<T>::add(std::string::const_iterator begin, std::string::const_iterator end, T value) {
	auto node = &_trie;
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
size_t Matcher<T>::match(char character) {
	if (_node == nullptr)
		return NO_MATCH_;
	auto nodeIterator = _node->children.find(character);
	if (nodeIterator == _node->children.end())
		return NO_MATCH_;
	//_node = &(*nodeIterator->second);
	_node = nodeIterator->second.get();
	if (_node->value)
		return FULL_MATCH_;
	return PARTIAL_MATCH_;
}

template<typename T>
std::string::const_iterator Matcher<T>::match(std::string::const_iterator begin, std::string::const_iterator end) {
	_node = &_trie;
	auto nextNode = _node;
	auto result = begin;
	for (auto iterator = begin; begin != end; iterator++) {
		auto nodeIterator = nextNode->children.find(*iterator);
		if (nodeIterator == nextNode->children.end()) break;
		nextNode = nodeIterator->second.get();
		if (nextNode->value.get()) {
			_node = nextNode;
			result = iterator + 1;
		}
	}
	return result;
}

template<typename T>
T * Matcher<T>::get() { return _node->value.get(); }

template<typename T>
void Matcher<T>::reset() { _node = &_trie; }

template class Matcher<Command * (*)(std::string, std::string)>;
template class Matcher<FieldFactory * (*)(std::string)>;
