/*
    module  : modf.c
    version : 1.6
    date    : 10/02/23
*/
#ifndef MODF_C
#define MODF_C

/**
OK 1620  modf  :  DAA	F  ->  G H
G is the fractional part and H is the integer part
(but expressed as a float) of F.
*/
void modf_(pEnv env)
{
    Node node;
    double exp;

    PARM(1, UFLOAT);
    env->stck = pvec_pop(env->stck, &node);
    node.u.dbl = modf(node.op == FLOAT_ ? node.u.dbl : node.u.num, &exp);
    node.op = FLOAT_;
    env->stck = pvec_add(env->stck, node);
    node.u.dbl = exp;
    node.op = FLOAT_;
    env->stck = pvec_add(env->stck, node);
}
#endif
