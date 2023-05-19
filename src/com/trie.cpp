#include "trie.h"

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
	auto nextNode = _node->children.find(character);
	if (nextNode == _node->children.end())
		return NO_MATCH_;
	_node = &(*nextNode->second);
	if (_node->value)
		return FULL_MATCH_;
	return PARTIAL_MATCH_;
}

template<typename T>
size_t Matcher<T>::match(std::string::const_iterator begin, std::string::const_iterator end) {
	Node<T> *node = nullptr;
	_node = &_trie;
	size_t result = 0;
	for (auto iterator = begin; begin != end; iterator++) {
		int matched = match(*iterator);
		if (matched == NO_MATCH_)
			break;
		if (matched == FULL_MATCH_) {
			node = _node;
			result = iterator - begin + 1;
		}
	}
	if (node == nullptr) {
		if (result == 0)
			return NO_MATCH_;
		return PARTIAL_MATCH_;//this doesnt make any sense?
							  //result = 0 implies no full matches have been found, but a partial match may have been
							  //therefore node == nullptr implies result == 0 implies NO_MATCH returned
	}
	_node = node;
	return result;
}

template<typename T>
T * Matcher<T>::get() { return _node->value.get(); }

template<typename T>
void Matcher<T>::reset() { _node = &_trie; }

template class Matcher<Command * (*)(std::string)>;
