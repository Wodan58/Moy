/*
    module  : gc.c
    version : 1.8
    date    : 06/20/22
*/
#ifndef GC_C
#define GC_C

/**
gc  :  ->
Initiates garbage collection.
*/
PRIVATE void do_gc(pEnv env)
{
    COMPILE;
    GC_gcollect();
}
#endif
