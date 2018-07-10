/*
    module  : gc.c
    version : 1.4
    date    : 07/10/18
*/
#ifndef GC_X
#define GC_C

/**
gc  :  ->
Initiates garbage collection.
*/
PRIVATE void do_gc(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    ck_collect();
}
#endif
