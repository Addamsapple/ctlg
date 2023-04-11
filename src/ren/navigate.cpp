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

//make function to centre item/column, which should be useful for redo/undo

int scrolledTowardStart(int &startingRC, const int rcs, const int minRC) {
	int newRCs = std::min(rcs, startingRC - minRC);
	startingRC -= newRCs;
	return newRCs;
}

int scrolledTowardEnd(int &startingRC, const int rcs, const int visibleRCs, const int maxRC) {
	int newRCs = std::min(rcs, std::max(maxRC - visibleRCs + 1, startingRC) - startingRC);
	startingRC += newRCs;
	return newRCs;
}

std::pair<int, int> movedTowardStart(int &startingRC, int &activeRC, const int rcs, const int minRC) {
	int newRCs = std::min(rcs, startingRC + activeRC - minRC);
	if (activeRC - newRCs < 0) {
		int moved = activeRC;
		activeRC = 0;
		return std::make_pair(moved, scrolledTowardStart(startingRC, newRCs - moved, minRC));
	}
	activeRC -= newRCs;
	return std::make_pair(newRCs, 0);
}

std::pair<int, int> movedTowardEnd(int &startingRC, int &activeRC, const int rcs, const int visibleRCs, const int maxRC) {
	int newRCs = std::min(rcs, maxRC - startingRC - activeRC);
	if (activeRC + newRCs > visibleRCs - 1) {
		int moved = visibleRCs - 1 - activeRC;
		activeRC = visibleRCs - 1;
		return std::make_pair(moved, scrolledTowardEnd(startingRC, newRCs - moved, visibleRCs, maxRC));
	}
	activeRC += newRCs;
	return std::make_pair(newRCs, 0);
}

void scrollUpThroughItems(const int items) {
	scrolledTowardStart(startingItem, items, 0);
}

void scrollDownThroughItems(const int items) {
	std::min(scrolledTowardEnd(startingItem, items, itemPadHeight, catalogue.items() - 1), itemPadHeight);
}

void scrollLeftThroughItems(const int columns) {
	scrolledTowardStart(startingItemColumn, columns, 0);
}

void scrollRightThroughItems(const int columns) {
	scrolledTowardEnd(startingItemColumn, columns, visibleItemColumns, catalogue.fields() - 1);
}

void moveUpThroughItems(const int items) {
	movedTowardStart(startingItem, selectedItem, items, 0);
}

void moveDownThroughItems(const int items) {
	movedTowardEnd(startingItem, selectedItem, items, itemPadHeight, catalogue.items() - 1);
}

void moveLeftThroughItems(const int columns) {
	movedTowardStart(startingItemColumn, selectedItemColumn, columns, 0);
}

void moveRightThroughItems(const int columns) {
	movedTowardEnd(startingItemColumn, selectedItemColumn, columns, visibleItemColumns, catalogue.fields() - 1);
}

void moveToItem(const int item) {
	if (startingItem + selectedItem > item)
		moveUpThroughItems(startingItem + selectedItem - item);
	else
		moveDownThroughItems(item - startingItem - selectedItem);
}

void moveToItemColumn(const int column) {
	if (startingItemColumn + selectedItemColumn > column)
		moveLeftThroughItems(startingItemColumn + selectedItemColumn - column);
	else
		moveRightThroughItems(column - startingItemColumn - selectedItemColumn);
}

//call updateIO() in main loop rather
void scrollLeftThroughIO(const int columns) {
	if (scrolledTowardStart(startingIOColumn, columns, 0) > 0)
		updateIO();
}

void scrollRightThroughIO(const int columns) {
	if (scrolledTowardEnd(startingIOColumn, columns, screenWidth, ioString.size() - 1) > 0)
		updateIO();
}

void moveLeftThroughIO(const int columns) {
	auto result = movedTowardStart(startingIOColumn, selectedIOColumn, columns, 0);
	if (std::get<0>(result) + std::get<1>(result) > 0)
		updateIO();
}

void moveRightThroughIO(const int columns) {
	auto result = movedTowardEnd(startingIOColumn, selectedIOColumn, columns, screenWidth, ioString.size() - 1);
	if (std::get<0>(result) + std::get<1>(result) > 0)
		updateIO();
}

void moveThroughIO(const int column) {
	if (startingIOColumn + selectedIOColumn > column)
		moveLeftThroughIO(startingIOColumn + selectedIOColumn - column);
	else
		moveRightThroughIO(column - startingIOColumn - selectedIOColumn);
}

