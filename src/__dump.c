/*
    module  : __dump.c
    version : 1.9
    date    : 09/19/24
*/
#ifndef __DUMP_C
#define __DUMP_C

/**
Q0  OK  1070  __dump  :  A  ->  [..]
debugging only: pushes the dump as a list.
*/
void __dump_(pEnv env)
{
    Node node;

    vec_init(node.u.lis);
    node.op = LIST_;
    vec_push(env->stck, node);
}
#endif
