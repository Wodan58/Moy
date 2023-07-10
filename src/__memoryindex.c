/*
    module  : __memoryindex.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef __MEMORYINDEX_C
#define __MEMORYINDEX_C

/**
OK 3080  __memoryindex  :  A	->  I
Pushes current value of memory.
*/
void __memoryindex_(pEnv env)
{
    Node node;

    node.u.num = GC_get_heap_size();
    node.op = INTEGER_;
    vec_push(env->stck, node);
}
#endif
