/*
    module  : fputch.c
    version : 1.10
    date    : 09/17/24
*/
#ifndef FPUTCH_C
#define FPUTCH_C

/**
Q0  OK  1950  fputch  :  A  S C  ->  S
[FOREIGN] The character C is written to the current position of stream S.
*/
void fputch_(pEnv env)
{
    Node elem, node;

    PARM(2, FREAD);
    elem = vec_pop(env->stck);
    node = vec_back(env->stck);
    putc(elem.u.num, node.u.fil);
}
#endif
