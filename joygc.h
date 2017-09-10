/*
    module  : joygc.h
    version : 1.5
    date    : 09/10/17
*/
#include "gc.h"

#define malloc(x)	GC_malloc(x)
#define realloc(x,y)	GC_realloc(x,y)
#define strdup(x)	GC_strdup(x)
#define free(x)
