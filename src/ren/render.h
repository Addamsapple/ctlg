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

//move to cpp file, not used by anything else
inline constexpr int NORMAL_ITEM = 1;
inline constexpr int HIGHLIGHTED_ITEM = 2;
inline constexpr int HIGHLIGHTED_FIELD = 3;
inline constexpr int NORMAL_TITLE = 7;
inline constexpr int NORMAL_IO = 4;
inline constexpr int IO_WARNING = 5;
inline constexpr int IO_ERROR = 6;

//screen variables
inline int screenWidth;
inline int screenHeight;

inline WINDOW *headerWindow;
inline WINDOW *itemWindow;
inline WINDOW *ioWindow;

//rename
inline int itemPadWidth;
inline int itemPadHeight;

//make this a size_t
inline int visibleItemColumns;//move this elsewhere?

//io variables
inline bool cursorEnabled;
//inline int ioColourPair;

//move to different file?
inline std::vector<char> ioString;

void initialize();
void load();
void terminate();

void enableCursor();
void disableCursor();

void setIOColourPair(const int colourPair);

void updateIO();

void refreshPads();

void mvwaddfield(WINDOW *window, int row, int column, const Field &field);
void mvwaddfields(WINDOW *window, int row, int column, const ConstFieldIterator &begin, const ConstFieldIterator &end);

void changeColumnColour(WINDOW *window, const int row, const int column, const int colour);
void changeItemColour(const int row, const int colour);

void highlightItem(const int row, const int column);
void unhighlightItem(const int row);

#endif
