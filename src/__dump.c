/*
    module  : __dump.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef __DUMP_C
#define __DUMP_C

/**
OK 1070  __dump  :  A	->  [..]
debugging only: pushes the dump as a list.
*/
void __dump_(pEnv env)
{
#ifndef COMPILER
    Node node;

    node.u.lis = 0;
    node.op = LIST_;
    lst_push(env->stck, node);
#endif
}
#endif
