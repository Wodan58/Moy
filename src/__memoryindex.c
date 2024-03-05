/*
    module  : __memoryindex.c
    version : 1.9
    date    : 03/05/24
*/
#ifndef __MEMORYINDEX_C
#define __MEMORYINDEX_C

/**
Q0  OK  3060  __memoryindex  :  A  ->  I
Pushes current value of memory.
*/
void __memoryindex_(pEnv env)
{
    Node node;

    if (env->ignore)
	node.u.num = 0;
    else
	node.u.num = GC_get_memory_use();
    node.op = INTEGER_;
    env->stck = pvec_add(env->stck, node);
}
#endif
