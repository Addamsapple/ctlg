#include "reset.h"

#include "interface.h"

Reset::Reset(std::string &&modifier, std::string &&arguments) {}

bool Reset::execute() {
	table.reset();
	return true;
}
