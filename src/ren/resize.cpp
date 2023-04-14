#include "interface.h"
#include "io.h"
#include "navigate.h"
#include "render.h"

//just resize windows unconditionally?
//and handle movement afterwards?
//e.g. if selectedItemColumn >= visibleItemColumns....
//or selectedItemColumn = std::min(selectedItemColumn, visibleItemColumns);
//selectedItem = std::min(selectedItem, itemPadHeight);
//
void resizeScreen() {
	int widthChange = getmaxx(stdscr) - screenWidth;
	if (widthChange != 0) {
		screenWidth += widthChange;
		wresize(ioWindow, IO_WINDOW_HEIGHT, screenWidth);
		//not updating itemPadWidth etc
		int visibleItemColumnChange = screenWidth / COLUMN_WIDTH - visibleItemColumns;
		visibleItemColumns += visibleItemColumnChange;
		if (visibleItemColumnChange != 0) {
			if (visibleItemColumnChange < 0)
				moveTowardLastItemColumn(0);
			else if (catalogue.fields() - startingItemColumn < visibleItemColumns && startingItemColumn > 0)
				scrollTowardFirstItemColumn(visibleItemColumnChange);
		}
		if (widthChange < 0)
			moveTowardLastIOColumn(0);
		else if (ioString.size() - startingIOColumn < screenWidth && startingIOColumn > 0)
			scrollTowardFirstIOColumn(widthChange);
	}
	int heightChange = getmaxy(stdscr) - screenHeight;
	if (heightChange != 0 && screenHeight + heightChange >= MINIMUM_SCREEN_HEIGHT) {
		screenHeight += heightChange;
		itemPadHeight += heightChange;
		wresize(itemWindow, itemPadHeight, itemPadWidth);
		//highlighted item moved off screen
		if (heightChange < 0)
			moveTowardLastItem(-1);
		else if (catalogue.items() - startingItem < itemPadHeight && startingItem > 0)
			scrollTowardFirstItem(heightChange);
	}
	updateIO();
}
