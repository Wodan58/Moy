/*
    module  : __memorymax.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef __MEMORYMAX_C
#define __MEMORYMAX_C

/**
OK 1160  __memorymax  :  A 	->  I
Pushes value of total size of memory.
*/
void __memorymax_(pEnv env)
{
#ifndef COMPILER
    Node node;

    node.u.num = GC_get_memory_use();
    node.op = INTEGER_;
    lst_push(env->stck, node);
#endif
}
#endif
