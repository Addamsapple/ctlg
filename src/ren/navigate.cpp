#include <algorithm>

#include "interface.h"
#include "navigate.h"
#include "render.h"

void populateTitles(const int sc, const int ec) {
	int ec_ = std::min(ec, std::min(visibleItemColumns, (int) catalogue.fields() - itemColumnView.firstElement()) - sc);//change variable types
	auto begin = catalogue.titles().cbegin() + itemColumnView.firstElement() + sc;
	mvwaddfields(headerWindow, 0, sc * COLUMN_WIDTH, begin, begin + ec_ - sc);
	wnoutrefresh(headerWindow);
}

void populateItems(const int sr, const int er, const int sc, const int ec) {
	int er_ = std::min(er, std::min(itemPadHeight, (int) catalogue.items() - itemView.firstElement()) - sr);
	int ec_ = std::min(ec, std::min(visibleItemColumns, (int) catalogue.fields() - itemColumnView.firstElement()) - sc);//change variable types
	auto ibegin = catalogue.cbegin() + itemView.firstElement() + sr;
	for (auto iterator = ibegin; iterator < ibegin + er_ - sr; iterator++) {
		auto fbegin = (*iterator).cbegin() + itemColumnView.firstElement() + sc;
		mvwaddfields(itemWindow, sr + (iterator - ibegin), sc * COLUMN_WIDTH, fbegin, fbegin + ec_ - sc);
		if (iterator - ibegin == itemView.selectedElement())
			for (size_t column = 0; column < ec_; column++) {
				if (column == itemColumnView.selectedElement())
					changeColumnColour(itemWindow, itemView.selectedElement(), column, HIGHLIGHTED_FIELD);
				else
					changeColumnColour(itemWindow, itemView.selectedElement(), column, HIGHLIGHTED_ITEM);
			}
	}
	//need to call wclrtobot() to clear excess lines
	wnoutrefresh(itemWindow);
}

//might need to redefine these to clear in case that columns are deleted
void clearExcessTitles() {
	int column = COLUMN_WIDTH * std::min((size_t) visibleItemColumns, catalogue.fields());
	if (column < itemPadWidth) {
		wmove(headerWindow, 0, column);
		wclrtoeol(headerWindow);
		wnoutrefresh(headerWindow);
	}
}

void clearExcessItemColumns() {
	int column = COLUMN_WIDTH * std::min((size_t) visibleItemColumns, catalogue.fields());
	if (column < itemPadWidth) {
		for (int item = 0; item < itemPadHeight && item < catalogue.items(); item++) {
			wmove(itemWindow, item, column);
			wclrtoeol(itemWindow);
		}
		wnoutrefresh(itemWindow);
	}
}

//still bugged
//using itemPadHeight, but that is not changed by resize.cpp
void clearExcessItems() {
	size_t item = catalogue.items() - itemView.firstElement();
	if (item < itemPadHeight) {
		wmove(itemWindow, item, 0);
		wclrtobot(itemWindow);
		wnoutrefresh(itemWindow);
	}
}

void populateScreen() {
	populateTitles(0, visibleItemColumns);
	clearExcessTitles();
	populateItems(0, itemPadHeight, 0, visibleItemColumns);
	clearExcessItemColumns();
	clearExcessItems();
}
