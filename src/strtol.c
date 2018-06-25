/*
    module  : strtol.c
    version : 1.5
    date    : 06/25/18
*/
#include "runtime.h"

/**
strtol  :  S I  ->  J
String S is converted to the integer J using base I.
If I = 0, assumes base 10,
but leading "0" means base 8 and leading "0x" means base 16.
*/
PRIVATE void do_strtol(void)
{
    int base;
    long_t num;

#ifndef NCHECK
    if (optimizing) {
	del_history(1);
	chg_history(INTEGER_);
    }
    if (optimizing && INTEGER_1 && STRING_2)
	;
    else
	COMPILE;
    TWOPARAMS("strtol");
    INTEGER("strtol");
#endif
    base = stk->u.num;
    POP(stk);
#ifndef NCHECK
    STRING("strtol");
#endif
#ifdef _MSC_VER
    num = strtol(stk->u.str, 0, base);
#else
    num = strtoll(stk->u.str, 0, base);
#endif
    if (OUTSIDE) {
	stk->u.num = num;
	stk->op = INTEGER_;
    } else
	UNARY(INTEGER_NEWNODE, num);
}
