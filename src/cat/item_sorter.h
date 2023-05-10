#include <vector>

template<typename T>
class Compare {
	protected:
		std::vector<int> _elements;

		auto _element(const T &t, const int element);
	public:
		Compare(std::vector<int> &&elements);

		bool operator()(const T &a, const T &b);
};

template<typename T>
std::vector<size_t> sortedOrder(const T &list, Compare<typename T::value_type> &&compare);

template<typename T>
std::vector<size_t> sortedOrder(const T &list, std::vector<size_t> indices, Compare<typename T::value_type> &&compare);
