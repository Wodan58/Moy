/*
    module  : true.c
    version : 1.7
    date    : 10/02/23
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
    env->stck = pvec_add(env->stck, node);
}
#endif
