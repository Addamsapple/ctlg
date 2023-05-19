#ifndef TYPE_PROC_H
#define TYPE_PROC_H

#include "item.h"
#include "processor.h"
#include "type_matcher.h"

//inline Processor<FieldConstructorConstructor, FieldConstructorInterface *&> typeProcessor;
inline TypeMatcher typeProcessor;

void loadTypes();

#endif
