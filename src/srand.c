/*
    module  : srand.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef SRAND_C
#define SRAND_C

/**
OK 1780  srand  :  D	I  ->
Sets the random integer seed to integer I.
*/
void srand_(pEnv env)
{
    Node node;

    PARM(1, UNMKTIME);
    env->stck = pvec_pop(env->stck, &node);
    srand(node.u.num);
}
#endif
