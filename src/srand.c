/*
    module  : srand.c
    version : 1.10
    date    : 09/17/24
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
    node = vec_pop(env->stck);
    srand(node.u.num);
}
#endif
