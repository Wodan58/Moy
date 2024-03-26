/*
    module  : srand.c
    version : 1.9
    date    : 03/21/24
*/
#ifndef SRAND_C
#define SRAND_C

/**
Q0  IGNORE_POP  1780  srand  :  D  I  ->
[IMPURE] Sets the random integer seed to integer I.
*/
void srand_(pEnv env)
{
    Node node;

    PARM(1, UNMKTIME);
    env->stck = pvec_pop(env->stck, &node);
    srand(node.u.num);
}
#endif
