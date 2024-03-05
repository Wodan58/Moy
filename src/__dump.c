/*
    module  : __dump.c
    version : 1.7
    date    : 03/05/24
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

    node.u.lis = 0;
    node.op = LIST_;
    env->stck = pvec_add(env->stck, node);
}
#endif
