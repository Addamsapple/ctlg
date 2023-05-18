#include <fstream>

#include "interface.h"
#include "write.h"

Write::Write(std::vector<std::string> args) : _file(std::move(args[0])) {}
bool Write::execute() {
	std::ofstream file(_file);
	file << table.types() << '\n';
	file << table.titles() << '\n';
	for (auto item = table.begin(); item != table.end(); item++)
		file << *item << '\n';
	return true;
}
