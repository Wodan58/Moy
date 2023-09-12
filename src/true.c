/*
    module  : true.c
    version : 1.5
    date    : 09/12/23
*/
#ifndef TRUE_C
#define TRUE_C

/**
IMMEDIATE 1010  true  :  A	->  true
Pushes the value true.
*/
void true_(pEnv env)
{
    Node node;

    node.u.num = 1;
    node.op = BOOLEAN_;
    lst_push(env->stck, node);
}
#endif
