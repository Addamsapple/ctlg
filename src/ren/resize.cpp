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
		//not updating itemPadWidth etc
		int visibleItemColumnChange = screenWidth / COLUMN_WIDTH - visibleItemColumns;
		visibleItemColumns += visibleItemColumnChange;
		if (visibleItemColumnChange != 0) {
			if (visibleItemColumnChange < 0)
				itemColumnView.moveForward(0);
			else if (catalogue.fields() - itemColumnView.firstElement() < visibleItemColumns && itemColumnView.firstElement() > 0)
				itemColumnView.scrollBackward(visibleItemColumnChange);
		}
		if (widthChange < 0)
			ioView.moveForward(0);
		else if (ioString.size() - ioView.firstElement() < screenWidth && ioView.firstElement() > 0)
			ioView.scrollBackward(widthChange);
	}
	int heightChange = getmaxy(stdscr) - screenHeight;
	if (heightChange != 0 && screenHeight + heightChange >= MINIMUM_SCREEN_HEIGHT) {
		screenHeight += heightChange;
		itemPadHeight += heightChange;
		wresize(itemWindow, itemPadHeight, itemPadWidth);
		if (heightChange < 0)
			itemView.moveForward(0);
		else if (catalogue.items() - itemView.firstElement() < itemPadHeight && itemView.firstElement() > 0)
			itemView.scrollBackward(heightChange);
	}
	updateIO();
}
