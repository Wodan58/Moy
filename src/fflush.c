/*
    module  : fflush.c
    version : 1.3
    date    : 09/04/23
*/
#ifndef FFLUSH_C
#define FFLUSH_C

/**
OK 1860  fflush  :  DA	S  ->  S
Flush stream S, forcing all buffered output to be written.
*/
void fflush_(pEnv env)
{
    Node node;

    PARM(1, FGET);
    node = lst_back(env->stck);
    fflush(node.u.fil);
}
#endif
