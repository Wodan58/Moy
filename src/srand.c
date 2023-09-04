/*
    module  : srand.c
    version : 1.3
    date    : 09/04/23
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
    node = lst_pop(env->stck);
    srand(node.u.num);
}
#endif
