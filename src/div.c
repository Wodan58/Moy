/*
    module  : div.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef DIV_C
#define DIV_C

/**
OK 1430  div  :  DDAA	I J  ->  K L
Integers K and L are the quotient and remainder of dividing I by J.
*/
void div_(pEnv env)
{
    lldiv_t result;
    Node first, second;

    PARM(2, DIV);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    result = lldiv(first.u.num, second.u.num);
    first.u.num = result.quot;
    lst_push(env->stck, first);
    first.u.num = result.rem;
    lst_push(env->stck, first);
}
#endif
