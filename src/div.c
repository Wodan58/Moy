/*
    module  : div.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef DIV_C
#define DIV_C

/**
OK 1430  div  :  DDAA	I J  ->  K L
Integers K and L are the quotient and remainder of dividing I by J.
*/
void div_(pEnv env)
{
    ldiv_t result;
    Node first, second;

    PARM(2, DIV);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    result = ldiv(first.u.num, second.u.num);
    first.u.num = result.quot;
    vec_push(env->stck, first);
    first.u.num = result.rem;
    vec_push(env->stck, first);
}
#endif
