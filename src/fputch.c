/*
    module  : fputch.c
    version : 1.9
    date    : 03/05/24
*/
#ifndef FPUTCH_C
#define FPUTCH_C

/**
Q0  OK  1950  fputch  :  A  S C  ->  S
[FOREIGN] The character C is written to the current position of stream S.
*/
void fputch_(pEnv env)
{
    Node node, elem;

    PARM(2, FREAD);
    env->stck = pvec_pop(env->stck, &elem);
    node = pvec_lst(env->stck);
    putc(elem.u.num, node.u.fil);
}
#endif
