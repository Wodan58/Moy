/*
    module  : trunc.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef TRUNC_C
#define TRUNC_C

/**
OK 1690  trunc  :  DA	F  ->  I
I is an integer equal to the float F truncated toward zero.
*/
void trunc_(pEnv env)
{
#ifndef COMPILER
    Node node;

    PARM(1, UFLOAT);
    node = lst_pop(env->stck);
    node.u.num = node.u.dbl;
    node.op = INTEGER_;
    lst_push(env->stck, node);
#endif
}
#endif
