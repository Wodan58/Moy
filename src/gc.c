/*
    module  : gc.c
    version : 1.3
    date    : 09/11/23
*/
#ifndef GC_C
#define GC_C

/**
OK 3010  gc  :  N	->
Initiates garbage collection.
*/
void gc_(pEnv env)
{
#ifndef COMPILER
    GC_gcollect();
#endif
}
#endif
