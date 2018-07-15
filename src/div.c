/*
    module  : div.c
    version : 1.7
    date    : 07/15/18
*/
#ifndef DIV_X
#define DIV_C

#ifdef NEW_RUNTIME
void do_div(void)
{
    ldiv_t result;

    TRACE;
    result = ldiv(stk[-2], stk[-1]);
    stk[-2] = result.quot;
    stk[-1] = result.rem;
}
#else
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
    if (OUTSIDE) {
	stk->next->u.num = result.quot;
	stk->u.num = result.rem;
	return;
    }
    BINARY(INTEGER_NEWNODE, result.quot);
    NULLARY(INTEGER_NEWNODE, result.rem);
}
#endif
#endif
