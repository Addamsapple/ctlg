#ifndef MATCHER__H
#define MATCHER__H

#include <limits>
#include <memory>
#include <unordered_map>

template<typename T>
struct Node {
	std::unordered_map<char, std::unique_ptr<Node>> children;
	std::unique_ptr<T> value;
};

static constexpr size_t NO_MATCH_ = std::numeric_limits<size_t>::max();
static constexpr size_t PARTIAL_MATCH_ = NO_MATCH_ - 1;
static constexpr size_t FULL_MATCH_ = PARTIAL_MATCH_ - 2;

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
		std::pair<T *, std::string::const_iterator> match(std::string::const_iterator begin, std::string::const_iterator end);
};

template<typename T>
class CharacterMatcher : public Trie<T> {
	protected:
		Node<T> *_matchedNode;
	public:
		CharacterMatcher();

		std::pair<T *, size_t> match(char character);

		void reset();
};

#endif
