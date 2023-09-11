/*
    module  : sin.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef SIN_C
#define SIN_C

/**
OK 1640  sin  :  DA	F  ->  G
G is the sine of F.
*/
void sin_(pEnv env)
{
#ifndef COMPILER
    Node node;

    PARM(1, UFLOAT);
    node = lst_pop(env->stck);
    node.u.dbl = sin(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    lst_push(env->stck, node);
#endif
}
#endif
