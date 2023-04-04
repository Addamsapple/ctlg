#include "interface.h"
#include "io.h"
#include "navigate.h"
#include "render.h"

//just resize windows unconditionally?
//and handle movement afterwards?
//e.g. if selectedItemColumn >= visibleItemColumns....
//or selectedItemColumn = std::min(selectedItemColumn, visibleItemColumns);
//selectedItem = std::min(selectedItem, itemPadHeight);
void resizeScreen() {
	int widthChange = getmaxx(stdscr) - screenWidth;
	if (widthChange != 0) {
		screenWidth += widthChange;
		wresize(ioWindow, IO_WINDOW_HEIGHT, screenWidth);
		int newVisibleItemColumns = screenWidth / COLUMN_WIDTH;
		if (visibleItemColumns != newVisibleItemColumns) {
			//highlighted item column moved off screen
			if (selectedItemColumn > newVisibleItemColumns - 1 && newVisibleItemColumns > 0)
				moveLeftThroughItems(visibleItemColumns - newVisibleItemColumns);
			visibleItemColumns = newVisibleItemColumns;
		}
		//highlighted IO column moved off screen
		if (selectedIOColumn > screenWidth - 1 && screenWidth > 0)
			moveLeftThroughIO(-widthChange);
	}
	int heightChange = getmaxy(stdscr) - screenHeight;
	if (heightChange != 0 && screenHeight + heightChange >= MINIMUM_SCREEN_HEIGHT) {
		screenHeight += heightChange;
		itemPadHeight += heightChange;
		wresize(itemWindow, itemPadHeight, itemPadWidth);
		//highlighted item moved off screen
		if (selectedItem > itemPadHeight - 1)
			moveUpThroughItems(-heightChange);
	}
	updateIO();
}
