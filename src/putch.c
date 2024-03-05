/*
    module  : putch.c
    version : 1.8
    date    : 03/05/24
*/
#ifndef PUTCH_C
#define PUTCH_C

/**
Q0  OK  3090  putch  :  D  N  ->
[IMPURE] N : numeric, writes character whose ASCII is N.
*/
void putch_(pEnv env)
{
    Node node;

    PARM(1, PREDSUCC);
    env->stck = pvec_pop(env->stck, &node);
    if (!env->ignore)
	putchar(node.u.num);
}
#endif
