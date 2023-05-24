#ifndef COMMAND_PROC_H
#define COMMAND_PROC_H

#include "command_matcher.h"

extern CharacterCommandMatcher incrementalProcessor;
extern StringCommandMatcher immediateProcessor;

void runCommand(char character);
void runCommand(std::string string);

#endif
