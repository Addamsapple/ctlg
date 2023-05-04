#include "read.h"

#include "interface.h"
#include "item.h"
#include "render.h"

void Read::_loadTypes() {
	std::string types;
	std::getline(_file, types);
	auto types_ = splitItem(types);
	for (size_t type = 0; type < types_.size(); type++)
		catalogue.insertColumn(std::move(types_[type]), "", std::vector<std::string>(), type);
}

void Read::_loadTitles() {
	std::string titles;
	std::getline(_file, titles);
	auto titles_ = splitItem(titles);
	for (size_t title = 0; title < titles_.size(); title++)
		catalogue.setTitle(std::move(titles_[title]), title);
}

#include <iostream>
#include "return.h"
void Read::_loadItems() {
	std::string item;
	std::getline(_file, item);
	while (std::getline(_file, item)) {
		std::cerr << item << '\n';
		//catalogue.insertItem(item, catalogue.items(), true);
		catalogue.appendItem(item, true);
		std::cerr << "items: " << catalogue.items() << '\n';
	}
	std::cerr << returnCode() << '\n';
}

void write(std::string  s) {
	std::ofstream f(s);
	f << catalogue.types() << '\n';
	f << catalogue.titles() << '\n';
	for (auto item = catalogue.begin(); item != catalogue.end(); item++)
		f << *item << '\n';
}

#include "commands.h"
bool Read::execute(StringVector arguments) {
	//catalogue.clear();
	_file.open(arguments[0]);
	_loadTypes();
	_loadTitles();
	_loadItems();
	resize();//this should not have to be called here.
	_file.close();
	//write("new");
	//auto c = new Load();
	//c->execute(arguments);
	//write("old");
	return true;
	//return c->execute(arguments);
	//Load().execute(arguments);
}
