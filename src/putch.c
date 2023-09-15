/*
    module  : putch.c
    version : 1.5
    date    : 09/15/23
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
    node = lst_pop(env->stck);
    putchar(node.u.num);
}
#endif
