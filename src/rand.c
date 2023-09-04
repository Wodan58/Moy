/*
    module  : rand.c
    version : 1.3
    date    : 09/04/23
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
    lst_push(env->stck, node);
}
#endif
