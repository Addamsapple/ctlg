#ifndef RENDER_H
#define RENDER_H

#include "catalogue.h"
#include "curses.h"

//move constants that are not used in other files to cpp file

//screen constants
inline constexpr int HEADER_PAD_HEIGHT = 1;
inline constexpr int IO_WINDOW_HEIGHT = 1;
inline constexpr int MINIMUM_SCREEN_HEIGHT = 5;

inline constexpr int FIELD_WIDTH = 15;
inline constexpr int PADDING_WIDTH = 5;
inline constexpr int COLUMN_WIDTH = FIELD_WIDTH + PADDING_WIDTH;

inline constexpr int MINIMUM_SCREEN_WIDTH = COLUMN_WIDTH;

inline constexpr int NORMAL_ITEM = 1;
inline constexpr int HIGHLIGHTED_ITEM = 2;
inline constexpr int HIGHLIGHTED_FIELD = 3;

//screen variables
inline int screenWidth;
inline int screenHeight;

inline WINDOW *headerPad;
inline WINDOW *itemPad;
inline WINDOW *ioWindow;

inline int itemPadWidth;
inline int itemPadHeight;

inline int visibleItemColumns;//move this elsewhere?

//io variables
inline bool cursorEnabled;

inline std::vector<char> ioString;


void initialize();
void load();
void terminate();

void enableCursor();
void disableCursor();

void pnoutrefreshHeaderPad();
void pnoutrefreshItemPad();

void updateIO();

void refreshPads();

void mvwaddfield(WINDOW *window, int row, int column, const Field &field);
void mvwcaddfield(WINDOW *window, int row, int column, short color, const Field &field);

void mvwadditem(WINDOW *window, int row, const Item &item);
void mvwadditems(WINDOW *window, int row, const ConstItemIterator begin, const ConstItemIterator end);

void changeItemColumnColour(const int row, const int column, const int colour);
void changeItemColour(const int row, const int colour);

void highlightItem(const int row, const int column);
void unhighlightItem(const int row);

#endif
