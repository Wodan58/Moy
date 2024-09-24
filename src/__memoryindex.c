/*
    module  : __memoryindex.c
    version : 1.11
    date    : 09/17/24
*/
#ifndef __MEMORYINDEX_C
#define __MEMORYINDEX_C

/**
Q0  IGNORE_PUSH  3060  __memoryindex  :  A  ->  I
Pushes current value of memory.
*/
void __memoryindex_(pEnv env)
{
    Node node;

    node.u.num = GC_get_memory_use();
    node.op = INTEGER_;
    vec_push(env->stck, node);
}
#endif
