/*
    module  : true.c
    version : 1.9
    date    : 09/17/24
*/
#ifndef TRUE_C
#define TRUE_C

/**
Q0  IMMEDIATE  1010  true  :  A  ->  true
Pushes the value true.
*/
void true_(pEnv env)
{
    Node node;

    node.u.num = 1;
    node.op = BOOLEAN_;
    vec_push(env->stck, node);
}
#endif
