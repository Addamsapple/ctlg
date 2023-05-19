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
class Matcher {
	protected:
		Node<T> _trie;
		Node<T> *_node;
	public:

		Matcher();

		void add(std::string::const_iterator begin, std::string::const_iterator end, T value);

		size_t match(char character);
		size_t match(std::string::const_iterator begin, std::string::const_iterator end);

		T * get();

		void reset();
};

#endif
