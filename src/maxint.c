/*
    module  : maxint.c
    version : 1.9
    date    : 03/05/24
*/
#ifndef MAXINT_C
#define MAXINT_C

/**
Q0  IMMEDIATE  1020  maxint  :  A  ->  maxint
Pushes largest integer (platform dependent). Typically it is 32 bits.
*/
void maxint_(pEnv env)
{
    Node node;

    node.u.num = MAXINT_;
    node.op = INTEGER_;
    env->stck = pvec_add(env->stck, node);
}
#endif
