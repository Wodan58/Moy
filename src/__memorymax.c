/*
    module  : __memorymax.c
    version : 1.8
    date    : 02/01/24
*/
#ifndef __MEMORYMAX_C
#define __MEMORYMAX_C

/**
OK 1160  __memorymax  :  A 	->  I
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
