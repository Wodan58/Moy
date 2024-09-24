/*
    module  : rand.c
    version : 1.10
    date    : 09/17/24
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
    vec_push(env->stck, node);
}
#endif
