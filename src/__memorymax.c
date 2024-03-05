/*
    module  : __memorymax.c
    version : 1.9
    date    : 03/05/24
*/
#ifndef __MEMORYMAX_C
#define __MEMORYMAX_C

/**
Q0  OK  1160  __memorymax  :  A  ->  I
Pushes value of total size of memory.
*/
void __memorymax_(pEnv env)
{
    Node node;

    if (env->ignore)
	node.u.num = 0;
    else
	node.u.num = GC_get_memory_use() + GC_get_free_bytes();
    node.op = INTEGER_;
    env->stck = pvec_add(env->stck, node);
}
#endif
