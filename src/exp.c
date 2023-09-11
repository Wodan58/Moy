/*
    module  : exp.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef EXP_C
#define EXP_C

/**
OK 1560  exp  :  DA	F  ->  G
G is e (2.718281828...) raised to the Fth power.
*/
void exp_(pEnv env)
{
#ifndef COMPILER
    Node node;

    PARM(1, UFLOAT);
    node = lst_pop(env->stck);
    node.u.dbl = exp(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    lst_push(env->stck, node);
#endif
}
#endif
