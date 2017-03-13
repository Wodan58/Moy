/*
    module  : div.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
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

#ifndef NCHECK
    if (optimizing && INTEGER_1 && INTEGER_2 && stk->u.num)
	;
    else
	COMPILE;
    TWOPARAMS("div");
    INTEGERS2("div");
    CHECKZERO("div");
#endif
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
