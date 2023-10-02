/*
    module  : maxint.c
    version : 1.7
    date    : 10/02/23
*/
#ifndef MAXINT_C
#define MAXINT_C

/**
IMMEDIATE 1020  maxint  :  A	->  maxint
Pushes largest integer (platform dependent). Typically it is 32 bits.
*/
void maxint_(pEnv env)
{
    Node node;

    node.u.num = MAXINT;
    node.op = INTEGER_;
    env->stck = pvec_add(env->stck, node);
}
#endif
