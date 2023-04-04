#ifndef NAVIGATE_H
#define NAVIGATE_H

#include <utility>

void updateTitlesLeftward(std::pair<int, int> motion);

inline int startingItem;
inline int startingItemColumn;

inline int selectedItem;
inline int selectedItemColumn;

inline int startingIOColumn;
inline int selectedIOColumn;

int scrolledTowardStart(int &startingRC, const int rcs, const int minRC);
int scrolledTowardEnd(int &startingRC, const int rcs, const int visibleRCs, const int maxRC);

std::pair<int, int> movedTowardStart(int &startingRC, int &activeRC, const int rcs, const int minRC);
std::pair<int, int> movedTowardEnd(int &startingRC, int &activeRC, const int rcs, const int visibleRCs, const int maxRC);

void scrollUpThroughItems(const int items);
void scrollDownThroughItems(const int items);
void scrollLeftThroughItems(const int columns);
void scrollRightThroughItems(const int columns);

void moveUpThroughItems(const int items);
void moveDownThroughItems(const int items);
void moveLeftThroughItems(const int columns);
void moveRightThroughItems(const int columns);

void moveToItem(const int item);
void moveToItemColumn(const int column);

void scrollLeftThroughIO(const int columns);
void scrollRightThroughIO(const int columns);

void moveLeftThroughIO(const int columns);
void moveRightThroughIO(const int columns);

void moveThroughIO(const int column);

void populateScreen();

#endif
