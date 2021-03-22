/*
    module  : gc.c
    version : 1.7
    date    : 03/15/21
*/
#ifndef GC_C
#define GC_C

/**
gc  :  ->
Initiates garbage collection.
*/
PRIVATE void do_gc(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    GC_gcollect();
}
#endif
