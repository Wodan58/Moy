/*
    module  : putch.c
    version : 1.9
    date    : 03/21/24
*/
#ifndef PUTCH_C
#define PUTCH_C

/**
Q0  IGNORE_POP  3090  putch  :  D  N  ->
[IMPURE] N : numeric, writes character whose ASCII is N.
*/
void putch_(pEnv env)
{
    Node node;

    PARM(1, PREDSUCC);
    env->stck = pvec_pop(env->stck, &node);
    putchar(node.u.num);
}
#endif
