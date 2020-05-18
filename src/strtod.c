/*
    module  : strtod.c
    version : 1.9
    date    : 03/28/20
*/
#ifndef STRTOD_C
#define STRTOD_C

/**
strtod  :  S  ->  R
String S is converted to the float R.
*/
PRIVATE void do_strtod(void)
{
#ifndef OLD_RUNTIME
    if (compiling && STRING_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("strtod");
    STRING("strtod");
    stk->u.num = strtod(stk->u.str, 0);
    stk->op = FLOAT_;
}
#endif
