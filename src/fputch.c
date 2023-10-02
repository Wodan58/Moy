/*
    module  : fputch.c
    version : 1.7
    date    : 10/02/23
*/
#ifndef FPUTCH_C
#define FPUTCH_C

/**
OK 1950  fputch  :  A	S C  ->  S
The character C is written to the current position of stream S.
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
