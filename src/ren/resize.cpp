#include "interface.h"
#include "io.h"
#include "populate.h"
#include "render.h"

int oldScreenWidth;
int oldScreenHeight;

#define ITEM_WINDOW_HEIGHT\
	screenHeight - HEADER_PAD_HEIGHT - IO_WINDOW_HEIGHT - 1

void sizeScreen() {
	wresize(headerWindow, HEADER_PAD_HEIGHT, screenWidth);
	wresize(itemWindow, ITEM_WINDOW_HEIGHT, headerWindowWidth);
	mvwin(itemWindow, HEADER_PAD_HEIGHT, 0);
	wresize(ioWindow, IO_WINDOW_HEIGHT, screenWidth);
	mvwin(ioWindow, HEADER_PAD_HEIGHT + itemWindowHeight + 1, 0);

	visibleItemColumns = screenWidth / COLUMN_WIDTH;//this must be called before viewports updated?

	oldScreenWidth = screenWidth;
	oldScreenHeight = screenHeight;

	itemView.selectElement(0);
	itemColumnView.selectElement(0);
}

//dont use catalogue.fields(), visibleItemColumns, etc?
//get access to said values using viewports, then need to define 
void resizeScreen() {
	int widthChange = screenWidth - oldScreenWidth;
	if (widthChange != 0) {
		oldScreenWidth += widthChange;
		wresize(headerWindow, headerWindowHeight, screenWidth);
		wresize(itemWindow, itemWindowHeight, screenWidth);
		wresize(ioWindow, ioWindowHeight, screenWidth);
		int visibleItemColumnChange = screenWidth / COLUMN_WIDTH - visibleItemColumns;
		visibleItemColumns += visibleItemColumnChange;
		if (visibleItemColumnChange < 0)
			itemColumnView.moveForward(0);
		else if (visibleItemColumnChange > 0 && catalogue.fields() - itemColumnView.firstElement() < visibleItemColumns && itemColumnView.firstElement() > 0)
			itemColumnView.scrollBackward(visibleItemColumnChange);
		if (widthChange < 0)
			ioView.moveForward(0);
		else if (ioString.size() - ioView.firstElement() < screenWidth && ioView.firstElement() > 0)
			ioView.scrollBackward(widthChange);
	}
	int heightChange = screenHeight - oldScreenHeight;
	if (heightChange != 0 && oldScreenHeight + heightChange > 0) {
		oldScreenHeight += heightChange;
		wresize(itemWindow, ITEM_WINDOW_HEIGHT, itemWindowWidth);
		mvwin(ioWindow, HEADER_PAD_HEIGHT + itemWindowHeight + 1, 0);
		if (heightChange < 0)
			itemView.moveForward(0);
		else if (catalogue.items() - itemView.firstElement() < itemWindowHeight && itemView.firstElement() > 0)
			itemView.scrollBackward(heightChange);
	}
	updateIO();//dont call this here
}
