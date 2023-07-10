/*
    module  : asin.c
    version : 1.1
    date    : 07/10/23
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
    node = vec_pop(env->stck);
    node.u.dbl = asin(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    vec_push(env->stck, node);
}
#endif
