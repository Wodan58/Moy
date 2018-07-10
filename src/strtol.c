/*
    module  : strtol.c
    version : 1.8
    date    : 07/10/18
*/
#ifndef STRTOL_X
#define STRTOL_C

#ifdef RUNTIME
void do_strtol(void)
{
    int base;

    TRACE;
    base = do_pop();
    stk[-1] = strtol((char *)stk[-1], 0, base);
}
#else
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
    if (OUTSIDE) {
	stk->u.num = num;
	stk->op = INTEGER_;
    } else
	UNARY(INTEGER_NEWNODE, num);
}
#endif
#endif
