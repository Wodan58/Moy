/*
    module  : putch.c
    version : 1.2
    date    : 08/23/23
*/
#ifndef PUTCH_C
#define PUTCH_C

/**
OK 3120  putch  :  D	N  ->
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
