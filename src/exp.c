/*
    module  : exp.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef EXP_C
#define EXP_C

/**
Q0  OK  1560  exp  :  DA  F  ->  G
G is e (2.718281828...) raised to the Fth power.
*/
void exp_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    env->stck = pvec_pop(env->stck, &node);
    node.u.dbl = exp(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    env->stck = pvec_add(env->stck, node);
}
#endif
