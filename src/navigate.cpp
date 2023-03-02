#include <algorithm>

#include "interface.h"
#include "navigate.h"
#include "render.h"

//define constants for std::get<x> designations

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

void insertItems(const int position, ConstItemIterator begin, ConstItemIterator end) {
	int insertions = std::min((int) (end - begin), itemPadHeight - position);
	wmove(itemPad, position, 0);
	winsdelln(itemPad, insertions);
	mvwadditems(itemPad, position, begin, begin + insertions);
}

void appendItems(const int position, ConstItemIterator begin, ConstItemIterator end) {
	int insertions = std::min((int) (end - begin), itemPadHeight - position);
	wmove(itemPad, position, 0);
	winsdelln(itemPad, -insertions);
	mvwadditems(itemPad, itemPadHeight - insertions, begin, begin + insertions);
}

void updateItemHighlight(const int moved) {
	if ((moved > 0 && (selectedItem - moved >= 0)) || (moved < 0 && (selectedItem - moved < itemPadHeight)))
		unhighlightItem(selectedItem - moved);
	highlightItem(selectedItem, startingItemColumn + selectedItemColumn);
}

void updateItemColumnHighlight(const int moved) {
	changeItemColumnColour(selectedItem, startingItemColumn + selectedItemColumn - moved, HIGHLIGHTED_ITEM);
	changeItemColumnColour(selectedItem, startingItemColumn + selectedItemColumn, HIGHLIGHTED_FIELD);
}

void scrollUpThroughItems(const int items) {
	int scrolled = scrolledTowardStart(startingItem, items, 0);
	if (scrolled > 0) {
		insertItems(0, catalogue.begin() + startingItem, catalogue.begin() + startingItem + scrolled);
		updateItemHighlight(-scrolled);
		pnoutrefreshItemPad();
	}
}

void scrollDownThroughItems(const int items) {
	int scrolled = std::min(scrolledTowardEnd(startingItem, items, itemPadHeight, catalogue.items() - 1), itemPadHeight);
	if (scrolled > 0) {
		appendItems(0, catalogue.begin() + startingItem + itemPadHeight - scrolled, catalogue.begin() + startingItem + itemPadHeight);
		updateItemHighlight(scrolled);
		pnoutrefreshItemPad();
	}
}

void scrollLeftThroughItems(const int columns) {
	int scrolled = scrolledTowardStart(startingItemColumn, columns, 0);
	if (scrolled > 0) {
		updateItemColumnHighlight(-scrolled);
		pnoutrefreshHeaderPad();
		pnoutrefreshItemPad();
	}
}

void scrollRightThroughItems(const int columns) {
	int scrolled = scrolledTowardEnd(startingItemColumn, columns, visibleItemColumns, catalogue.fields() - 1);
	if (scrolled > 0) {
		updateItemColumnHighlight(scrolled);
		pnoutrefreshHeaderPad();
		pnoutrefreshItemPad();
	}
}

void moveUpThroughItems(const int items) {
	auto result = movedTowardStart(startingItem, selectedItem, items, 0);
	int moved = std::get<0>(result);
	int scrolled = std::get<1>(result);
	if (scrolled > 0)
		insertItems(0, catalogue.begin() + startingItem, catalogue.begin() + startingItem + scrolled);
	if (moved + scrolled > 0) {
		updateItemHighlight(-(moved + scrolled));
		pnoutrefreshItemPad();
	}
}

void moveDownThroughItems(const int items) {
	auto result = movedTowardEnd(startingItem, selectedItem, items, itemPadHeight, catalogue.items() - 1);
	int moved = std::get<0>(result);
	int scrolled = std::min(std::get<1>(result), itemPadHeight);
	if (scrolled > 0)
		appendItems(0, catalogue.begin() + startingItem + itemPadHeight - scrolled, catalogue.begin() + startingItem + itemPadHeight);
	if (moved + scrolled > 0) {
		updateItemHighlight(moved + scrolled);
		pnoutrefreshItemPad();
	}
}

void moveLeftThroughItems(const int columns) {
	auto result = movedTowardStart(startingItemColumn, selectedItemColumn, columns, 0);
	int moved = std::get<0>(result);
	int scrolled = std::get<1>(result);
	if (moved + scrolled > 0) {
		updateItemColumnHighlight(-(moved + scrolled));
		if (scrolled > 0)
			pnoutrefreshHeaderPad();
		pnoutrefreshItemPad();
	}
}

void moveRightThroughItems(const int columns) {
	auto result = movedTowardEnd(startingItemColumn, selectedItemColumn, columns, visibleItemColumns, catalogue.fields() - 1);
	int moved = std::get<0>(result);
	int scrolled = std::get<1>(result);
	if (moved + scrolled > 0) {
		updateItemColumnHighlight(moved + scrolled);
		if (scrolled > 0)
			pnoutrefreshHeaderPad();
		pnoutrefreshItemPad();
	}
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
