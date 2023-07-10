/*
    module  : exp.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef EXP_C
#define EXP_C

/**
OK 1560  exp  :  DA	F  ->  G
G is e (2.718281828...) raised to the Fth power.
*/
void exp_(pEnv env)
{
    Node node;

    PARM(1, UFLOAT);
    node = vec_pop(env->stck);
    node.u.dbl = exp(node.op == FLOAT_ ? node.u.dbl : (double)node.u.num);
    node.op = FLOAT_;
    vec_push(env->stck, node);
}
#endif
