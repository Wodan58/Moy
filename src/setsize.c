/*
    module  : setsize.c
    version : 1.10
    date    : 09/17/24
*/
#ifndef SETSIZE_C
#define SETSIZE_C

/**
Q0  OK  1030  setsize  :  A  ->  setsize
Pushes the maximum number of elements in a set (platform dependent).
Typically it is 32, and set members are in the range 0..31.
*/
void setsize_(pEnv env)
{
    Node node;

    node.u.num = SETSIZE;
    node.op = INTEGER_;
    vec_push(env->stck, node);
}
#endif
