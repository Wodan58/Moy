/*
    module  : putch.c
    version : 1.10
    date    : 09/17/24
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
    node = vec_pop(env->stck);
    putchar(node.u.num);
}
#endif
