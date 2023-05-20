#ifndef COMMAND_PROC_H
#define COMMAND_PROC_H


#include "commands.h"

#include "command_matcher.h"

//inline Processor<CommandConstructor> incrementalProcessor;
inline CharacterCommandMatcher incrementalProcessor;
//inline Processor<CommandConstructor> immediateProcessor;
//
inline StringCommandMatcher immediateProcessor;

void loadCommands();

#endif
