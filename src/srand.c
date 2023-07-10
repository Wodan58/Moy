/*
    module  : srand.c
    version : 1.1
    date    : 07/10/23
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
    node = vec_pop(env->stck);
    srand(node.u.num);
}
#endif
