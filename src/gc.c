/*
    module  : gc.c
    version : 1.5
    date    : 07/15/18
*/
#ifndef GC_X
#define GC_C

/**
gc  :  ->
Initiates garbage collection.
*/
PRIVATE void do_gc(void)
{
#ifdef NEW_RUNTIME
    TRACE;
#endif
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ck_collect();
}
#endif
