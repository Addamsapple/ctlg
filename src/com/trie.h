#include <memory>
#include <unordered_map>

template<typename T>
struct Node {
	std::unordered_map<char, std::unique_ptr<Node>> children;
	std::unique_ptr<T> value;
};

static constexpr int NO_MATCH = 0;
static constexpr int PARTIAL_MATCH = 1;
static constexpr int FULL_MATCH = 2;

template<typename T>
class Matcher {
	protected:
		Node<T> _trie;
		Node<T> *_node;
	public:

		Matcher();

		void add(const std::string &string, T value);

		int match(char character);
		int match(const std::string &string);

		T * get();

		void reset();
};
