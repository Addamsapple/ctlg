#ifndef MATCHER__H
#define MATCHER__H

#include <memory>
#include <unordered_map>

template<typename T>
struct Node {
	std::unordered_map<char, std::unique_ptr<Node>> children;
	std::unique_ptr<T> value;
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
		std::pair<const T *, std::string::const_iterator> match(std::string::const_iterator begin, std::string::const_iterator end) const;
};

template<typename T>
class CharacterMatcher : public Trie<T> {
	protected:
		Node<T> *_matchedNode;
	public:
		CharacterMatcher();

		std::pair<const T *, int> match(char character);

		void reset();
};

static constexpr int NO_MATCH_ = -1;
static constexpr int PARTIAL_MATCH_ = 0;
static constexpr int FULL_MATCH_ = 1;

#endif
