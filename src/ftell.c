/*
    module  : ftell.c
    version : 1.9
    date    : 03/05/24
*/
#ifndef FTELL_C
#define FTELL_C

/**
Q0  OK 1990  ftell  :  A  S  ->  S I
[FOREIGN] I is the current position of stream S.
*/
void ftell_(pEnv env)
{
    Node node;

    PARM(1, FGET);
    node = pvec_lst(env->stck);
    node.u.num = ftell(node.u.fil);
    node.op = INTEGER_;
    env->stck = pvec_add(env->stck, node);
}
#endif
