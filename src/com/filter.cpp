#include "filter.h"
#include "interface.h"

Filter::Filter(std::string &&modifier, std::string &&arguments) {}

bool Filter::execute() {
	table.filter([count = size_t(0)](ItemView) mutable { return count++ & 1; });
	return true;
}
