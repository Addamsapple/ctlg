#ifndef COMMAND_PROC_H
#define COMMAND_PROC_H


#include "commands.h"
#include "processor.h"

#include "command_matcher.h"

inline Processor<CommandConstructor> incrementalProcessor;
//inline Processor<CommandConstructor> immediateProcessor;
//
inline CommandMatcher immediateProcessor;

void loadCommands();

#endif
