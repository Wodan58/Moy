/*
    module  : div.c
    version : 1.10
    date    : 06/20/22
*/
#ifndef DIV_C
#define DIV_C

/**
div  :  I J  ->  K L
Integers K and L are the quotient and remainder of dividing I by J.
*/
PRIVATE void do_div(pEnv env)
{
    ldiv_t result;

    TWOPARAMS("div");
    INTEGERS2("div");
    CHECKZERO("div");
    result = ldiv(env->stk->next->u.num, env->stk->u.num);
    BINARY(INTEGER_NEWNODE, result.quot);
    NULLARY(INTEGER_NEWNODE, result.rem);
}
#endif
