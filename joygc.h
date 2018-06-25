/*
    module  : joygc.h
    version : 1.6
    date    : 12/27/17
*/
#include "gc.h"

#ifdef strdup
#undef strdup
#endif

#define malloc(x)	GC_malloc(x)
#define realloc(x,y)	GC_realloc(x,y)
#define strdup(x)	GC_strdup(x)
#define free(x)
