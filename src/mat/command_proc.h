#ifndef COMMAND_PROC_H
#define COMMAND_PROC_H

#include "command_matcher.h"

inline CharacterCommandMatcher incrementalProcessor;
inline StringCommandMatcher immediateProcessor;

//TODO: construct above matchers without load command?
void loadCommands();

void runCommand(char character);
void runCommand(std::string string);

#endif
