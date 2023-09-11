/*
    module  : __memoryindex.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef __MEMORYINDEX_C
#define __MEMORYINDEX_C

/**
OK 3060  __memoryindex  :  A	->  I
Pushes current value of memory.
*/
void __memoryindex_(pEnv env)
{
#ifndef COMPILER
    Node node;

    node.u.num = GC_get_memory_use() - GC_get_free_bytes();
    node.op = INTEGER_;
    lst_push(env->stck, node);
#endif
}
#endif
