/*
    module  : __dump.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef __DUMP_C
#define __DUMP_C

/**
OK 1070  __dump  :  A	->  [..]
debugging only: pushes the dump as a list.
*/
void __dump_(pEnv env)
{
    Node node;

    node.u.lis = 0;
    node.op = LIST_;
    lst_push(env->stck, node);
}
#endif
