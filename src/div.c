/*
    module  : div.c
    version : 1.8
    date    : 09/17/24
*/
#ifndef DIV_C
#define DIV_C

/**
Q0  OK  1430  div  :  DDAA  I J  ->  K L
Integers K and L are the quotient and remainder of dividing I by J.
*/
void div_(pEnv env)
{
    Node first, second;
    int64_t quotient, remainder;

    PARM(2, DIV);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    quotient = first.u.num / second.u.num;
    remainder = first.u.num % second.u.num;
    first.u.num = quotient;
    vec_push(env->stck, first);
    first.u.num = remainder;
    vec_push(env->stck, first);
}
#endif
