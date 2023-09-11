/*
    module  : rand.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef RAND_C
#define RAND_C

/**
OK 1150  rand  :  A	->  I
I is a random integer.
*/
void rand_(pEnv env)
{
#ifndef COMPILER
    Node node;

    node.u.num = rand();
    node.op = INTEGER_;
    lst_push(env->stck, node);
#endif
}
#endif
