#include "read.h"

#include "interface.h"
#include "item.h"
#include "render.h"

void Read::_loadTypes() {
	std::string types;
	std::getline(_file, types);
	auto types_ = splitItem(types);
	for (size_t type = 0; type < types_.size(); type++) {
		//consider allocating vector outside of loop
		std::vector<std::string> fields;
		fields.push_back(std::move(types_[type]));
		fields.push_back(std::string());
		table.insertColumn(std::move(fields), type);
	}
}

void Read::_loadTitles() {
	std::string titles;
	std::getline(_file, titles);
	auto titles_ = splitItem(titles);
	for (size_t title = 0; title < titles_.size(); title++)
		table.setTitle(std::move(titles_[title]), title);
}

void Read::_loadItems() {
	std::string item;
	//std::getline(_file, item);//first item skipped when this was uncommented!!!
	while (std::getline(_file, item))
		table.insertItem(item, table.items(), true);
}

bool Read::execute(StringVector arguments) {
	//table.clear();
	_file.open(arguments[0]);
	_loadTypes();
	_loadTitles();
	_loadItems();
	resize();//this should not have to be called here.
	_file.close();
	return true;
}
