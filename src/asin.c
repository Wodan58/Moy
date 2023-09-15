/*
    module  : asin.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef ASIN_C
#define ASIN_C

/**
OK 1500  asin  :  DA	F  ->  G
G is the arc sine of F.
*/
void asin_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    node = lst_pop(env->stck);
    node.u.dbl = asin(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    lst_push(env->stck, node);
}
#endif
