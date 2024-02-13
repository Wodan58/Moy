/*
    module  : rand.c
    version : 1.7
    date    : 02/01/24
*/
#ifndef RAND_C
#define RAND_C

/**
OK 1150  rand  :  A	->  I
[IMPURE] I is a random integer.
*/
void rand_(pEnv env)
{
    Node node;

    if (env->ignore)
	node.u.num = 0;
    else
	node.u.num = rand();
    node.op = INTEGER_;
    env->stck = pvec_add(env->stck, node);
}
#endif
