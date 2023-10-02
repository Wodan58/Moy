/*
    module  : fflush.c
    version : 1.7
    date    : 10/02/23
*/
#ifndef FFLUSH_C
#define FFLUSH_C

/**
OK 1860  fflush  :  N	S  ->  S
Flush stream S, forcing all buffered output to be written.
*/
void fflush_(pEnv env)
{
    Node node;

    PARM(1, FGET);
    node = pvec_lst(env->stck);
    fflush(node.u.fil);
}
#endif
