#ifndef COMMAND_PROC_H
#define COMMAND_PROC_H

#include "command_matcher.h"

inline CharacterCommandMatcher incrementalProcessor;
inline StringCommandMatcher immediateProcessor;

void loadCommands();

#endif
