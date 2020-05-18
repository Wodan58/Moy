/*
    module  : strtol.c
    version : 1.10
    date    : 03/28/20
*/
#ifndef STRTOL_C
#define STRTOL_C

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

#ifndef OLD_RUNTIME
    if (compiling && INTEGER_1 && STRING_2)
	;
    else
	COMPILE;
#endif
    TWOPARAMS("strtol");
    INTEGER("strtol");
    base = stk->u.num;
    POP(stk);
    STRING("strtol");
#ifdef _MSC_VER
    num = strtol(stk->u.str, 0, base);
#else
    num = strtoll(stk->u.str, 0, base);
#endif
    stk->u.num = num;
    stk->op = INTEGER_;
}
#endif
