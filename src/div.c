/*
    module  : div.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef DIV_C
#define DIV_C

/**
Q0  OK  1430  div  :  DDAA  I J  ->  K L
Integers K and L are the quotient and remainder of dividing I by J.
*/
void div_(pEnv env)
{
    lldiv_t result;
    Node first, second;

    PARM(2, DIV);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    result = lldiv(first.u.num, second.u.num);
    first.u.num = result.quot;
    env->stck = pvec_add(env->stck, first);
    first.u.num = result.rem;
    env->stck = pvec_add(env->stck, first);
}
#endif
