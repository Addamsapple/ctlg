#include "filter.h"
#include "interface.h"

Filter::Filter(std::string &&modifier, std::string &&arguments) {}

class Filterer {
	private:
		size_t n = 0;
	public:
		bool operator()(ItemView view) {
			n++;
			return n & 1;
		}
};

bool Filter::execute() {
	table.filter(Filterer());
	return true;
}
