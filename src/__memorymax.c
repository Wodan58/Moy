/*
    module  : __memorymax.c
    version : 1.11
    date    : 09/17/24
*/
#ifndef __MEMORYMAX_C
#define __MEMORYMAX_C

/**
Q0  IGNORE_PUSH  1160  __memorymax  :  A  ->  I
Pushes value of total size of memory.
*/
void __memorymax_(pEnv env)
{
    Node node;

    node.u.num = GC_get_memory_use() + GC_get_free_bytes();
    node.op = INTEGER_;
    vec_push(env->stck, node);
}
#endif
