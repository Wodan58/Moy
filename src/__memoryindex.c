/*
    module  : __memoryindex.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef __MEMORYINDEX_C
#define __MEMORYINDEX_C

/**
OK 3060  __memoryindex  :  A	->  I
Pushes current value of memory.
*/
void __memoryindex_(pEnv env)
{
    Node node;

    node.u.num = GC_get_memory_use() - GC_get_free_bytes();
    node.op = INTEGER_;
    lst_push(env->stck, node);
}
#endif
