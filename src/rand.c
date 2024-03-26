/*
    module  : rand.c
    version : 1.9
    date    : 03/21/24
*/
#ifndef RAND_C
#define RAND_C

/**
Q0  IGNORE_PUSH  1150  rand  :  A  ->  I
[IMPURE] I is a random integer.
*/
void rand_(pEnv env)
{
    Node node;

    node.u.num = rand();
    node.op = INTEGER_;
    env->stck = pvec_add(env->stck, node);
}
#endif
