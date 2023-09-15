/*
    module  : sin.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef SIN_C
#define SIN_C

/**
OK 1640  sin  :  DA	F  ->  G
G is the sine of F.
*/
void sin_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    node = lst_pop(env->stck);
    node.u.dbl = sin(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    lst_push(env->stck, node);
}
#endif
