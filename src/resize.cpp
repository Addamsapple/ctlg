#include "interface.h"
#include "io.h"
#include "navigate.h"
#include "render.h"

void resizeScreen() {
	bool screenRefreshRequired = false;
	bool headerPadRefreshRequired = false;
	bool itemPadRefreshRequired = false;
	int widthChange = getmaxx(stdscr) - screenWidth;
	//screen width changed
	if (widthChange != 0) {
		screenWidth += widthChange;
		wresize(ioWindow, IO_WINDOW_HEIGHT, screenWidth);
		int newVisibleItemColumns = screenWidth / COLUMN_WIDTH;
		if (visibleItemColumns != newVisibleItemColumns) {
			//visible item columns decreased
			if (visibleItemColumns > newVisibleItemColumns) {
				//highlighted item column moved off screen
				if (selectedItemColumn > newVisibleItemColumns - 1 && newVisibleItemColumns > 0)
					moveLeftThroughItems(visibleItemColumns - newVisibleItemColumns);
				screenRefreshRequired = true;
			}
			headerPadRefreshRequired = true;
			itemPadRefreshRequired = true;
			visibleItemColumns = newVisibleItemColumns;
		//screen width decreased, but not enough to cut off last item column
		} else if (widthChange < 0)
			untouchwin(stdscr);
		//highlighted IO column moved off screen
		if (selectedIOColumn > screenWidth - 1 && screenWidth > 0)
			moveLeftThroughIO(-widthChange);
	}
	int heightChange = getmaxy(stdscr) - screenHeight;
	//screen height changed
	if (heightChange != 0 && screenHeight + heightChange >= MINIMUM_SCREEN_HEIGHT) {
		screenHeight += heightChange;
		itemPadHeight += heightChange;
		wresize(itemPad, itemPadHeight, itemPadWidth);
		//screen height increased
		if (heightChange > 0) {
			auto itemIterator = catalogue.begin() + startingItem + itemPadHeight - heightChange;
			mvwadditems(itemPad, itemPadHeight - heightChange, itemIterator, itemIterator + heightChange);
			itemPadRefreshRequired = true;
		//highlighted item moved off screen
		} else if (selectedItem > itemPadHeight - 1) {
			moveUpThroughItems(-heightChange);
			itemPadRefreshRequired = true;
		}
		mvwin(ioWindow, screenHeight - IO_WINDOW_HEIGHT, 0);
		touchline(stdscr, screenHeight - (IO_WINDOW_HEIGHT + 1), IO_WINDOW_HEIGHT + 1);
		screenRefreshRequired = true;
	}
	if (screenRefreshRequired)
		wnoutrefresh(stdscr);
	if (headerPadRefreshRequired)
		pnoutrefreshHeaderPad();
	if (itemPadRefreshRequired)
		pnoutrefreshItemPad();
	updateIO();
}
