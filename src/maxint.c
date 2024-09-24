/*
    module  : maxint.c
    version : 1.10
    date    : 09/17/24
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
    vec_push(env->stck, node);
}
#endif
