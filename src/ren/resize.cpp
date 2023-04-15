#include "interface.h"
#include "io.h"
#include "populate.h"
#include "render.h"

int oldScreenWidth = 1;
int oldScreenHeight = 1;

/*
void sizeScreen() {
	headerWindow = newwin(HEADER_PAD_HEIGHT, std::max(screenWidth, 1), 0, 0);
	itemWindow = newwin(std::max(screenHeight - HEADER_PAD_HEIGHT - IO_WINDOW_HEIGHT - 1, 1), headerWindowWidth, HEADER_PAD_HEIGHT, 0);
	ioWindow = newwin(IO_WINDOW_HEIGHT, headerWindowWidth, HEADER_PAD_HEIGHT + itemWindowHeight + 1, 0);
}
*/

//dont use catalogue.fields(), visibleItemColumns, etc?
//get access to said values using viewports, then need to define 
void resizeScreen() {
	int widthChange = screenWidth - oldScreenWidth;
	if (widthChange != 0) {
		oldScreenWidth += widthChange;
		wresize(ioWindow, IO_WINDOW_HEIGHT, ioWindowWidth + widthChange);
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
	int heightChange = screenHeight - oldScreenHeight;
	if (heightChange != 0 && screenHeight + heightChange >= MINIMUM_SCREEN_HEIGHT) {
		oldScreenHeight += heightChange;
		wresize(itemWindow, itemWindowHeight + heightChange, itemWindowWidth);
		if (heightChange < 0)
			itemView.moveForward(0);
		else if (catalogue.items() - itemView.firstElement() < itemWindowHeight && itemView.firstElement() > 0)
			itemView.scrollBackward(heightChange);
	}
	updateIO();
}
