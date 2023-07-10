/*
    module  : gc.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef GC_C
#define GC_C

/**
OK 3030  gc  :  N	->
Initiates garbage collection.
*/
void gc_(pEnv env)
{
    GC_gcollect();
    env->nothing++;
}
#endif
