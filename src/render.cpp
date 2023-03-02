#include "io.h"
#include "interface.h"
#include "navigate.h"
#include "render.h"

//forward declarations
void disableCursor();

void pnoutrefreshHeaderPad();
void pnoutrefreshItemPad();

void mvwadditem(WINDOW *window, int row, const Item &item);
void mvwadditems(WINDOW *window, int row, const ConstItemIterator begin, const ConstItemIterator end);

void highlightItem(const int row, const int column);

void initialize() {
	setlocale(LC_ALL, "");
	//initialize screen
	initscr(); cbreak(); noecho();
	//enable colours
	start_color();
	init_pair(NORMAL_ITEM, COLOR_WHITE, COLOR_BLACK);
	init_pair(HIGHLIGHTED_ITEM, COLOR_WHITE, COLOR_CYAN);
	init_pair(HIGHLIGHTED_FIELD, COLOR_WHITE, COLOR_YELLOW);
	//initialize variables
	screenWidth = std::max(getmaxx(stdscr), MINIMUM_SCREEN_WIDTH);
	screenHeight = std::max(getmaxy(stdscr), MINIMUM_SCREEN_HEIGHT);
	itemPadWidth = screenWidth;
	itemPadHeight = screenHeight - HEADER_PAD_HEIGHT - IO_WINDOW_HEIGHT - 2;
	//initialize pads/windows
	headerPad = newpad(HEADER_PAD_HEIGHT, screenWidth);
	itemPad = newpad(itemPadHeight, screenWidth);
	ioWindow = newwin(IO_WINDOW_HEIGHT, screenWidth, screenHeight - IO_WINDOW_HEIGHT, 0);
	//configure keyboard
	set_escdelay(50);
	intrflush(ioWindow, FALSE);
	keypad(ioWindow, TRUE);
	disableCursor();
	//prevent screen clear on first refresh() call
	untouchwin(stdscr);
}

//give fields argument?
void load() {
	itemPadWidth = std::max(COLUMN_WIDTH * (int) catalogue.fields(), MINIMUM_SCREEN_WIDTH);
	//allocate memory to pads
	wresize(headerPad, HEADER_PAD_HEIGHT, itemPadWidth);
	wresize(itemPad, itemPadHeight, itemPadWidth);
	//move this stuff to interface?
	//initialize variables
	startingItem = 0;
	startingItemColumn = 0;
	selectedItem = 0;
	selectedItemColumn = 0;
	visibleItemColumns = screenWidth / COLUMN_WIDTH;
	//clear windows
	werase(headerPad);
	werase(itemPad);
	//move populate stuff to interface? so can use for different catalogue objects, etc.
	//populate windows
	mvwadditem(headerPad, 0, catalogue.titleHeader());
	//VERY SLOPPY
	mvwadditems(itemPad, 0, catalogue.begin() + startingItem, catalogue.begin() + std::min(startingItem + itemPadHeight, (int) catalogue.items()));//int cast necessary?
	setOutput("");
	//highlight first item
	highlightItem(selectedItem, startingItemColumn + selectedItemColumn);
	//refresh screen
	touchwin(stdscr);
	wnoutrefresh(stdscr);
	pnoutrefreshHeaderPad();
	pnoutrefreshItemPad();
	doupdate();
}

void terminate() {
	endwin();
}

void enableCursor() {
	curs_set(2);
	cursorEnabled = true;
	wmove(ioWindow, 0, selectedIOColumn);
}

void disableCursor() {
	curs_set(0);
	cursorEnabled = false;
}

//rename these to say, updateScreenHeader, updateScreenItems, updateScreenIO, etc
void pnoutrefreshHeaderPad() {
	pnoutrefresh(headerPad, 0, COLUMN_WIDTH * startingItemColumn, 0, 0, HEADER_PAD_HEIGHT - 1, COLUMN_WIDTH * visibleItemColumns - 1);
}

//consider expanding to allow for only certain lines/columns to be redrawn, instead of having to redraw all of them each time, (esp. for screen resizing)
void pnoutrefreshItemPad() {
	pnoutrefresh(itemPad, 0, COLUMN_WIDTH * startingItemColumn, HEADER_PAD_HEIGHT + 1, 0, HEADER_PAD_HEIGHT + 1 + itemPadHeight - 1, COLUMN_WIDTH * visibleItemColumns - 1);
}

void updateIO() {
	werase(ioWindow);
	mvwaddnstr(ioWindow, 0, 0, ioString.data() + startingIOColumn, screenWidth - 1);
	if (cursorEnabled)
		wmove(ioWindow, 0, selectedIOColumn);
	wnoutrefresh(ioWindow);
}

//rename
/*void refreshPads() {
	pnoutrefreshHeaderPad();
	pnoutrefreshItemPad();
	//pnoutrefreshInputPad();
	doupdate();
}*/

void mvwaddfield(WINDOW *window, int row, int column, const Field &field) {
	if (field.length() > FIELD_WIDTH) {
		mvwaddnstr(window, row, column, field.c_str(), FIELD_WIDTH - 3);
		waddstr(window, "...");
	} else
		mvwaddstr(window, row, column, field.c_str());
}

void mvwadditem(WINDOW *window, int row, const Item &item) {
	auto begin = item.cbegin();
	auto end = item.cend();
	for (auto iterator = begin; iterator != end; iterator++)
		mvwaddfield(window, row, (iterator - begin) * COLUMN_WIDTH, **iterator);
}

void mvwadditems(WINDOW *window, int row, const ConstItemIterator begin, const ConstItemIterator end) {
	for (auto iterator = begin; iterator != end; iterator++)
		mvwadditem(window, row + iterator - begin, *iterator);
}

void changeItemColumnColour(const int row, const int column, const int colour) {
	mvwchgat(itemPad, row, COLUMN_WIDTH * column, COLUMN_WIDTH, A_NORMAL, colour, NULL);
}

void changeItemColour(const int row, const int colour) {
	mvwchgat(itemPad, row, 0, -1, A_NORMAL, colour, NULL);
}

void highlightItem(const int row, const int column) {
	changeItemColour(row, HIGHLIGHTED_ITEM);
	changeItemColumnColour(row, column, HIGHLIGHTED_FIELD);
}

void unhighlightItem(const int row) {
	changeItemColour(row, NORMAL_ITEM);
}
