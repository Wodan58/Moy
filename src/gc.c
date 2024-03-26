/*
    module  : gc.c
    version : 1.8
    date    : 03/21/24
*/
#ifndef GC_C
#define GC_C

/**
Q0  IGNORE_OK  3010  gc  :  N  ->
[IMPURE] Initiates garbage collection.
*/
void gc_(pEnv env)
{
    GC_gcollect();
}
#endif
