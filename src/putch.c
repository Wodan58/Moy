/*
    module  : putch.c
    version : 1.1
    date    : 07/10/23
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
    node = vec_pop(env->stck);
    putchar(node.u.num);
}
#endif
