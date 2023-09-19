/*
    module  : __memorymax.c
    version : 1.6
    date    : 09/19/23
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

    node.u.num = GC_get_memory_use() + GC_get_free_bytes();
    node.op = INTEGER_;
    lst_push(env->stck, node);
}
#endif
