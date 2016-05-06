/*
    module  : strtol.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
strtol  :  S I  ->  J
String S is converted to the integer J using base I.
If I = 0, assumes base 10,
but leading "0" means base 8 and leading "0x" means base 16.
*/
/* strtol.c */
PRIVATE void strtol_(void)
{
    int base;

    TWOPARAMS("strtol");
    INTEGER("strtol");
    base = stk->u.num;
    POP(stk);
    STRING("strtol");
    if (OUTSIDE) {
#ifdef BIT_32
	stk->u.num = strtol(stk->u.str, 0, base);
#else
	stk->u.num = strtoll(stk->u.str, 0, base);
#endif
	stk->op = INTEGER_;
	return;
    }
#ifdef BIT_32
    UNARY(INTEGER_NEWNODE, strtol(stk->u.str, 0, base));
#else
    UNARY(INTEGER_NEWNODE, strtoll(stk->u.str, 0, base));
#endif
}
