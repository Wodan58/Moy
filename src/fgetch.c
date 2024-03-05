/*
    module  : fgetch.c
    version : 1.9
    date    : 03/05/24
*/
#ifndef FGETCH_C
#define FGETCH_C

/**
Q0  OK  1870  fgetch  :  A  S  ->  S C
[FOREIGN] C is the next available character from stream S.
*/
void fgetch_(pEnv env)
{
    Node node;

    PARM(1, FGET);
    node = pvec_lst(env->stck);
    node.u.num = getc(node.u.fil);
    node.op = CHAR_;
    env->stck = pvec_add(env->stck, node);
}
#endif
