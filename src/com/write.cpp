#include <fstream>

#include "interface.h"
#include "write.h"

bool Write::execute(StringVector arguments) {
	std::ofstream file(arguments[0]);
	file << table.types() << '\n';
	file << table.titles() << '\n';
	for (auto item = table.begin(); item != table.end(); item++)
		file << *item << '\n';
	return true;
}
