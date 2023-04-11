#include <fstream>

#include "interface.h"
#include "write.h"

bool Write::execute(StringVector arguments) {
	std::ofstream file(arguments[0]);
	file << catalogue.types() << '\n';
	file << catalogue.titles() << '\n';
	for (auto item = catalogue.begin(); item != catalogue.end(); item++)
		file << *item << '\n';
	return true;
}
