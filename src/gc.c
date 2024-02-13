/*
    module  : gc.c
    version : 1.6
    date    : 02/01/24
*/
#ifndef GC_C
#define GC_C

/**
OK 3010  gc  :  N	->
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
