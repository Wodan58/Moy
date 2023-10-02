/*
    module  : putch.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef PUTCH_C
#define PUTCH_C

/**
OK 3090  putch  :  D	N  ->
N : numeric, writes character whose ASCII is N.
*/
void putch_(pEnv env)
{
    Node node;

    PARM(1, PREDSUCC);
    env->stck = pvec_pop(env->stck, &node);
    putchar(node.u.num);
}
#endif
