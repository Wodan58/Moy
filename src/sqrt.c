/*
    module  : sqrt.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef SQRT_C
#define SQRT_C

/**
OK 1660  sqrt  :  DA	F  ->  G
G is the square root of F.
*/
void sqrt_(pEnv env)
{
#ifndef COMPILER
    Node node;

    PARM(1, UFLOAT);
    node = lst_pop(env->stck);
    node.u.dbl = sqrt(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    lst_push(env->stck, node);
#endif
}
#endif
