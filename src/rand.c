/*
    module  : rand.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef RAND_C
#define RAND_C

/**
OK 1150  rand  :  A	->  I
I is a random integer.
*/
void rand_(pEnv env)
{
    Node node;

    node.u.num = rand();
    node.op = INTEGER_;
    env->stck = pvec_add(env->stck, node);
}
#endif
