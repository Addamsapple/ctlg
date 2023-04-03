#ifndef COMMAND_PROC_H
#define COMMAND_PROC_H

#include "commands.h"
#include "processor.h"

inline Processor<CommandConstructor> incrementalProcessor;
inline Processor<CommandConstructor> immediateProcessor;

void loadCommands();

#endif
