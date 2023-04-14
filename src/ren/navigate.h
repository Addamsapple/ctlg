#ifndef NAVIGATE_H
#define NAVIGATE_H

inline int startingItem;
inline int startingItemColumn;

inline int selectedItem;
inline int selectedItemColumn;

inline int startingIOColumn;
inline int selectedIOColumn;

void populateScreen();

void moveTowardFirstItem(int items);
void moveTowardLastItem(int items);

void scrollTowardFirstItem(int items);
void scrollTowardLastItem(int items);

void moveTowardFirstItemColumn(int columns);
void moveTowardLastItemColumn(int items);

void scrollTowardFirstItemColumn(int columns);
void scrollTowardLastItemColumn(int columns);

void moveTowardFirstIOColumn(int columns);
void moveTowardLastIOColumn(int columns);

void scrollTowardFirstIOColumn(int columns);
void scrollTowardLastIOColumn(int columns);

#endif
