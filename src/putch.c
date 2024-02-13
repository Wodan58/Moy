/*
    module  : putch.c
    version : 1.7
    date    : 02/01/24
*/
#ifndef PUTCH_C
#define PUTCH_C

/**
OK 3090  putch  :  D	N  ->
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
