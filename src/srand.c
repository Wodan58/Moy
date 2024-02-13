/*
    module  : srand.c
    version : 1.7
    date    : 02/01/24
*/
#ifndef SRAND_C
#define SRAND_C

/**
OK 1780  srand  :  D	I  ->
[IMPURE] Sets the random integer seed to integer I.
*/
void srand_(pEnv env)
{
    Node node;

    PARM(1, UNMKTIME);
    env->stck = pvec_pop(env->stck, &node);
    if (!env->ignore)
	srand(node.u.num);
}
#endif
