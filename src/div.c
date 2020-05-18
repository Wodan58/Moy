/*
    module  : div.c
    version : 1.8
    date    : 03/28/20
*/
#ifndef DIV_C
#define DIV_C

/**
div  :  I J  ->  K L
Integers K and L are the quotient and remainder of dividing I by J.
*/
PRIVATE void do_div(void)
{
#ifdef _MSC_VER
    ldiv_t result;
#else
    lldiv_t result;
#endif

#ifndef OLD_RUNTIME
    if (compiling && INTEGER_1 && INTEGER_2 && stk->u.num)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("div");
    INTEGERS2("div");
    CHECKZERO("div");
#ifdef _MSC_VER
    result = ldiv(stk->next->u.num, stk->u.num);
#else
    result = lldiv(stk->next->u.num, stk->u.num);
#endif
    stk->next->u.num = result.quot;
    stk->u.num = result.rem;
}
#endif
