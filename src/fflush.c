/*
    module  : fflush.c
    version : 1.10
    date    : 09/17/24
*/
#ifndef FFLUSH_C
#define FFLUSH_C

/**
Q0  OK  1860  fflush  :  N  S  ->  S
[FOREIGN] Flush stream S, forcing all buffered output to be written.
*/
void fflush_(pEnv env)
{
    Node node;

    PARM(1, FGET);
    node = vec_back(env->stck);
    fflush(node.u.fil);
}
#endif
