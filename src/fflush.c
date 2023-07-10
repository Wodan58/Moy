/*
    module  : fflush.c
    version : 1.1
    date    : 07/10/23
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
    node = vec_back(env->stck);
    fflush(node.u.fil);
}
#endif
