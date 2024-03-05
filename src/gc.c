/*
    module  : gc.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef GC_C
#define GC_C

/**
Q0  OK  3010  gc  :  N  ->
[IMPURE] Initiates garbage collection.
*/
void gc_(pEnv env)
{
    if (env->ignore)
	return;
    GC_gcollect();
    /* nothing */
}
#endif
