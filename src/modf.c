/*
    module  : modf.c
    version : 1.4
    date    : 09/11/23
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
#ifndef COMPILER
    Node node;
    double exp;

    PARM(1, UFLOAT);
    node = lst_pop(env->stck);
    node.u.dbl = modf(node.op == FLOAT_ ? node.u.dbl : node.u.num, &exp);
    node.op = FLOAT_;
    lst_push(env->stck, node);
    node.u.dbl = exp;
    node.op = FLOAT_;
    lst_push(env->stck, node);
#endif
}
#endif
