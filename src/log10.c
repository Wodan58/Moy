/*
    module  : log10.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef LOG10_C
#define LOG10_C

/**
OK 1610  log10  :  DA	F  ->  G
G is the common logarithm of F.
*/
void log10_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    node = lst_pop(env->stck);
    node.u.dbl = log10(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    lst_push(env->stck, node);
}
#endif
