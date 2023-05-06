#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>

#include "catalogue.h"
#include "undoable_table.h"

inline UndoableTable catalogue;

void run(const std::string &command);

#endif
