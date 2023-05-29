#ifndef TRIE_H
#define TRIE_H

#include <memory>
#include <optional>
#include <unordered_map>

template<typename T>
struct Node {
	std::unordered_map<char, std::unique_ptr<Node>> children;
	std::optional<T> value;
};

template<typename T>
class Trie {
	protected:
		Node<T> _root;
	public:
		void add(std::string::const_iterator begin, std::string::const_iterator end, T value);
};

template<typename T>
class StringMatcher : public Trie<T> {
	public:
		std::pair<const T * const, std::string::const_iterator> match(std::string::const_iterator begin, std::string::const_iterator end) const noexcept;
};

enum class MatchResult {
	NoMatch,
	PartialMatch,
	FullMatch
};

template<typename T>
class CharacterMatcher : public Trie<T> {
	protected:
		mutable const Node<T> *_matchedNode;
	public:
		CharacterMatcher();

		std::pair<const T * const, MatchResult> match(char character) const noexcept;

		void reset() const noexcept;
};

#endif
