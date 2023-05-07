#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>

#include "table_actions.h"
//#include "table.h"
#include "undoable_table.h"

inline UndoableTable table;

void run(const std::string &command);

#endif
