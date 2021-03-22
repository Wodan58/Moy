/*
    module  : div.c
    version : 1.9
    date    : 03/15/21
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

#ifndef OLD_RUNTIME
    if (compiling && INTEGER_1 && INTEGER_2 && env->stk->u.num)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("div");
    INTEGERS2("div");
    CHECKZERO("div");
    result = ldiv(env->stk->next->u.num, env->stk->u.num);
    env->stk->next->u.num = result.quot;
    env->stk->u.num = result.rem;
}
#endif
