/*
    module  : cosh.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef COSH_C
#define COSH_C

/**
OK 1550  cosh  :  DA	F  ->  G
G is the hyperbolic cosine of F.
*/
void cosh_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    node = lst_pop(env->stck);
    node.u.dbl = cosh(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    lst_push(env->stck, node);
}
#endif
