#ifndef NAVIGATE_H
#define NAVIGATE_H

#include "viewport.h"
#include "render.h"
#include "interface.h"

inline Viewport itemView(
		[]() -> int {return itemPadHeight;},
		[]() -> int {return catalogue.items();}
);

inline Viewport itemColumnView(
		[]() -> int {return visibleItemColumns;},
		[]() -> int {return catalogue.fields();}
);

inline Viewport ioView(
		[]() -> int {return screenWidth;},
		[]() -> int {return ioString.size();}
);

void populateScreen();

#endif
