/*
    module  : asin.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef ASIN_C
#define ASIN_C

/**
OK 1500  asin  :  DA	F  ->  G
G is the arc sine of F.
*/
void asin_(pEnv env)
{
#ifndef COMPILER
    Node node;

    PARM(1, UFLOAT);
    node = lst_pop(env->stck);
    node.u.dbl = asin(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    lst_push(env->stck, node);
#endif
}
#endif
