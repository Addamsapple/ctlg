#include <algorithm>

#include "interface.h"
#include "navigate.h"
#include "render.h"

void populateTitles(const int sc, const int ec) {
	int ec_ = std::min(ec, std::min(visibleItemColumns, (int) catalogue.fields() - startingItemColumn) - sc);//change variable types
	auto begin = catalogue.titles().cbegin() + startingItemColumn + sc;
	mvwaddfields(headerWindow, 0, sc * COLUMN_WIDTH, begin, begin + ec_ - sc);
	wnoutrefresh(headerWindow);
}

void populateItems(const int sr, const int er, const int sc, const int ec) {
	int er_ = std::min(er, std::min(itemPadHeight, (int) catalogue.items() - startingItem) - sr);
	int ec_ = std::min(ec, std::min(visibleItemColumns, (int) catalogue.fields() - startingItemColumn) - sc);//change variable types
	auto ibegin = catalogue.cbegin() + startingItem + sr;
	for (auto iterator = ibegin; iterator < ibegin + er_ - sr; iterator++) {
		auto fbegin = (*iterator).cbegin() + startingItemColumn + sc;
		mvwaddfields(itemWindow, sr + (iterator - ibegin), sc * COLUMN_WIDTH, fbegin, fbegin + ec_ - sc);
		if (iterator - ibegin == selectedItem)
			for (size_t column = 0; column < ec_; column++) {
				if (column == selectedItemColumn)
					changeColumnColour(itemWindow, selectedItem, column, HIGHLIGHTED_FIELD);
				else
					changeColumnColour(itemWindow, selectedItem, column, HIGHLIGHTED_ITEM);
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
	size_t item = catalogue.items() - startingItem;
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

template<const int & (*Function)(const int &, const int &)>
int moveTowardBound(int &rc, int rcs, int &rcBound) {
	int moved = Function(rc + rcs, rcBound) - rc;
	rc += moved;
	return moved;
}

void moveTowardStart(int &startingRC, int &selectedRC, int rcs, int minStartingRC, int minSelectedRC) {
	int moved = moveTowardBound<std::max<int>>(selectedRC, -rcs, minSelectedRC);
	int scrolled = moveTowardBound<std::max<int>>(startingRC, -rcs - moved, minStartingRC);
}

void moveTowardEnd(int &startingRC, int &selectedRC, int rcs, int maxStartingRC, int maxSelectedRC) {
	int moved = moveTowardBound<std::min<int>>(selectedRC, rcs, maxSelectedRC);
	int scrolled = moveTowardBound<std::min<int>>(startingRC, rcs - moved, maxStartingRC);
}

void scrollTowardStart(int &startingRC, int &selectedRC, int rcs, int minStartingRC, int maxSelectedRC) {
	int scrolled = moveTowardBound<std::max<int>>(startingRC, -rcs, minStartingRC);
	int moved = moveTowardBound<std::min<int>>(selectedRC, -scrolled, maxSelectedRC);
}

void scrollTowardEnd(int &startingRC, int &selectedRC, int rcs, int maxStartingRC, int minSelectedRC) {
	int scrolled = moveTowardBound<std::min<int>>(startingRC, rcs, maxStartingRC);
	int moved = moveTowardBound<std::max<int>>(selectedRC, -scrolled, minSelectedRC);
}

void moveTowardFirstItem(int items) {
	moveTowardStart(startingItem, selectedItem, items, 0, 0);
}

void moveTowardLastItem(int items) {
	moveTowardEnd(startingItem, selectedItem, items, std::max((int) catalogue.items() - itemPadHeight, 0), std::min((int) catalogue.items(), itemPadHeight) - 1);
}

void scrollTowardFirstItem(int items) {
	scrollTowardStart(startingItem, selectedItem, items, 0, std::min((int) catalogue.items(), itemPadHeight) - 1);
}

void scrollTowardLastItem(int items) {
	scrollTowardEnd(startingItem, selectedItem, items, std::max((int) catalogue.items() - itemPadHeight, 0), 0);
}

void moveTowardFirstItemColumn(int columns) {
	moveTowardStart(startingItemColumn, selectedItemColumn, columns, 0, 0);
}

void moveTowardLastItemColumn(int columns) {
	moveTowardEnd(startingItemColumn, selectedItemColumn, columns, std::max((int) catalogue.fields() - visibleItemColumns, 0), std::min((int) catalogue.fields(), visibleItemColumns) - 1);
}

void scrollTowardFirstItemColumn(int columns) {
	scrollTowardStart(startingItemColumn, selectedItemColumn, columns, 0, std::min((int) catalogue.fields(), visibleItemColumns) - 1);
}

void scrollTowardLastItemColumn(int columns) {
	scrollTowardEnd(startingItemColumn, selectedItemColumn, columns, std::max((int) catalogue.fields() - visibleItemColumns, 0), 0);
}

void moveTowardFirstIOColumn(int columns) {
	moveTowardStart(startingIOColumn, selectedIOColumn, columns, 0, 0);
}

void moveTowardLastIOColumn(int columns) {
	moveTowardEnd(startingIOColumn, selectedIOColumn, columns, std::max((int) ioString.size() - screenWidth, 0), std::min((int) ioString.size(), screenWidth) - 1);
}

void scrollTowardFirstIOColumn(int columns) {
	scrollTowardStart(startingIOColumn, selectedIOColumn, columns, 0, std::min((int) ioString.size(), screenWidth) - 1);
}

void scrollTowardLastIOColumn(int columns) {
	scrollTowardEnd(startingIOColumn, selectedIOColumn, columns, std::max((int) ioString.size() - screenWidth, 0), 0);
}
