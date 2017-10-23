/*
    module  : gc.c
    version : 1.1
    date    : 03/12/17
*/
#include "runtime.h"

/*
gc  ->
Initiates garbage collection.
*/
PRIVATE void do_gc(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    GC_gcollect();
}
