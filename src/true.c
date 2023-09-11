/*
    module  : true.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef TRUE_C
#define TRUE_C

/**
IMMEDIATE 1010  true  :  A	->  true
Pushes the value true.
*/
void true_(pEnv env)
{
#ifndef COMPILER
    Node node;

    node.u.num = 1;
    node.op = BOOLEAN_;
    lst_push(env->stck, node);
#endif
}
#endif
