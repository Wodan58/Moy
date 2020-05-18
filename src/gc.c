/*
    module  : gc.c
    version : 1.6
    date    : 03/28/20
*/
#ifndef GC_C
#define GC_C

/**
gc  :  ->
Initiates garbage collection.
*/
PRIVATE void do_gc(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    ck_collect();
}
#endif
