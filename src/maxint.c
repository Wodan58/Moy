/*
    module  : maxint.c
    version : 1.2
    date    : 08/23/23
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
    lst_push(env->stck, node);
}
#endif
