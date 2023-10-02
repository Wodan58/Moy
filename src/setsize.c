/*
    module  : setsize.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef SETSIZE_C
#define SETSIZE_C

/**
OK 1030  setsize  :  A	->  setsize
Pushes the maximum number of elements in a set (platform dependent).
Typically it is 32, and set members are in the range 0..31.
*/
void setsize_(pEnv env)
{
    Node node;

    node.u.num = SETSIZE;
    node.op = INTEGER_;
    env->stck = pvec_add(env->stck, node);
}
#endif
