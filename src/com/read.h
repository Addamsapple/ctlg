#include <fstream>

#include "command.h"

COMMAND(
	Read,
		std::string _filename;
		std::ifstream _file;
		void _loadTypes();
		void _loadTitles();
		void _loadItems();
);
