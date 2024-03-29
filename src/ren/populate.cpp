#include <algorithm>

#include "interface.h"
#include "render.h"
#include "viewport.h"

int itemColumns() {
	return itemWindowWidth / COLUMN_WIDTH;
}

Viewport itemView(
		[]() -> int {return itemWindowHeight;},
		[]() -> int {return table.items();}
);

Viewport itemColumnView(
		itemColumns,
		[]() -> int {return table.fields();}
);

Viewport ioView(
		[]() -> int {return ioWindowWidth;},
		[]() -> int {return ioString.size();}
);

void populateTitles(const int sc, const int ec) {
	int ec_ = std::min(ec, std::min(itemColumns(), (int) table.fields() - itemColumnView.firstElement()) - sc);//change variable types
	auto begin = table.titles().begin() + itemColumnView.firstElement() + sc;
	mvwaddfields(headerWindow, 0, sc * COLUMN_WIDTH, begin, begin + ec_ - sc);
	wnoutrefresh(headerWindow);
}

void populateItems(const int sr, const int er, const int sc, const int ec) {
	int er_ = std::min(er, std::min(itemWindowHeight, (int) table.items() - itemView.firstElement()) - sr);
	int ec_ = std::min(ec, std::min(itemColumns(), (int) table.fields() - itemColumnView.firstElement()) - sc);//change variable types
	auto ibegin = table.begin() + itemView.firstElement() + sr;
	for (auto iterator = ibegin; iterator < ibegin + er_ - sr; iterator++) {
		auto fbegin = (*iterator).begin() + itemColumnView.firstElement() + sc;
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
	int column = COLUMN_WIDTH * std::min((size_t) itemColumns(), table.fields());
	if (column < itemWindowWidth) {
		wmove(headerWindow, 0, column);
		wclrtoeol(headerWindow);
		wnoutrefresh(headerWindow);
	}
}

void clearExcessItemColumns() {
	int column = COLUMN_WIDTH * std::min((size_t) itemColumns(), table.fields());
	if (column < itemWindowWidth) {
		for (int item = 0; item < itemWindowHeight && item < table.items(); item++) {
			wmove(itemWindow, item, column);
			wclrtoeol(itemWindow);
		}
		wnoutrefresh(itemWindow);
	}
}

//still bugged
void clearExcessItems() {
	size_t item = table.items() - itemView.firstElement();
	if (item < itemWindowHeight) {
		wmove(itemWindow, item, 0);
		wclrtobot(itemWindow);
		wnoutrefresh(itemWindow);
	}
}

void populateScreen() {
	populateTitles(0, itemColumns());
	clearExcessTitles();
	populateItems(0, itemWindowHeight, 0, itemColumns());
	clearExcessItemColumns();
	clearExcessItems();
}
