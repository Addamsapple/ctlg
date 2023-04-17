#include "io.h"
#include "interface.h"
#include "populate.h"
#include "render.h"

#define ITEM_WINDOW_HEIGHT\
	screenHeight - HEADER_PAD_HEIGHT - IO_WINDOW_HEIGHT - 1

//forward declarations
void disableCursor();

void initialize() {
	curses_trace(TRACE_CALLS);//for debugging
	setlocale(LC_ALL, "");
	//initialize screen
	initscr(); cbreak(); noecho();
	//enable colours
	start_color();
	init_pair(NORMAL_ITEM, COLOR_WHITE, COLOR_BLACK);
	init_pair(HIGHLIGHTED_ITEM, COLOR_BLACK, COLOR_CYAN);
	init_pair(HIGHLIGHTED_FIELD, COLOR_BLACK, COLOR_YELLOW);
	init_pair(NORMAL_TITLE, COLOR_BLACK, COLOR_GREEN);
	init_pair(NORMAL_IO, COLOR_WHITE, COLOR_BLACK);
	init_pair(IO_WARNING, COLOR_WHITE, COLOR_YELLOW);
	init_pair(IO_ERROR, COLOR_WHITE, COLOR_RED);//change to RED
	//initialize windows
	headerWindow = newwin(1, 1, 0, 0);
	itemWindow = newwin(1, 1, 0, 0);
	ioWindow = newwin(1, 1, 0, 0);
	//configure keyboard
	set_escdelay(50);
	intrflush(ioWindow, FALSE);
	keypad(ioWindow, TRUE);
	disableCursor();
	//prevent screen clear on first refresh() call
	//untouchwin(stdscr);//is this necessary?
	wattr_set(headerWindow, A_NORMAL, NORMAL_TITLE, 0);
}

void resize() {
	wresize(headerWindow, HEADER_PAD_HEIGHT, screenWidth);
	wresize(itemWindow, ITEM_WINDOW_HEIGHT, headerWindowWidth);
	mvwin(itemWindow, HEADER_PAD_HEIGHT, 0);
	wresize(ioWindow, IO_WINDOW_HEIGHT, screenWidth);
	mvwin(ioWindow, HEADER_PAD_HEIGHT + itemWindowHeight + 1, 0);
}

void terminate() {
	endwin();
}

void enableCursor() {
	curs_set(2);
	cursorEnabled = true;
	wmove(ioWindow, 0, ioView.selectedElement());
}

void disableCursor() {
	curs_set(0);
	cursorEnabled = false;
}

void updateIO() {
	werase(ioWindow);
	mvwaddnstr(ioWindow, 0, 0, ioString.data() + ioView.firstElement(), ioWindowWidth - 1);
	if (cursorEnabled)
		wmove(ioWindow, 0, ioView.selectedElement());
	wnoutrefresh(ioWindow);
}

void mvwaddfield(WINDOW *window, int row, int column, const Field &field) {
	if (field.length() > FIELD_WIDTH) {
		mvwaddnstr(window, row, column, field.c_str(), FIELD_WIDTH - 3);
		waddstr(window, "...");
	} else {
		mvwaddstr(window, row, column, field.c_str());
		for (int character = field.length(); character < FIELD_WIDTH; character++)
			waddch(window, ' ');
	}
	for (int character = 0; character < PADDING_WIDTH; character++)
		waddch(window, ' ');
}

void mvwaddfields(WINDOW *window, int row, int column, const ConstFieldIterator &begin, const ConstFieldIterator &end) {
	for (auto iterator = begin; iterator != end; iterator++)
		mvwaddfield(window, row, (column + (iterator - begin)) * COLUMN_WIDTH, **iterator);
}

void changeColumnColour(WINDOW* window, const int row, const int column, const int colour) {
	mvwchgat(itemWindow, row, COLUMN_WIDTH * column, COLUMN_WIDTH, A_NORMAL, colour, NULL);
}
