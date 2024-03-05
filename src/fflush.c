/*
    module  : fflush.c
    version : 1.9
    date    : 03/05/24
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
    node = pvec_lst(env->stck);
    fflush(node.u.fil);
}
#endif
