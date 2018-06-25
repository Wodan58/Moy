/*
    module  : gc.c
    version : 1.2
    date    : 06/25/18
*/
#include "runtime.h"

/**
gc  :  ->
Initiates garbage collection.
*/
PRIVATE void do_gc(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    GC_gcollect();
}
