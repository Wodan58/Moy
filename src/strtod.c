/*
    module  : strtod.c
    version : 1.7
    date    : 07/10/18
*/
#ifndef STRTOD_X
#define STRTOD_C

/**
strtod  :  S  ->  R
String S is converted to the float R.
*/
PRIVATE void do_strtod(void)
{
#ifndef NCHECK
    if (compiling && STRING_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("strtod");
    STRING("strtod");
    if (OUTSIDE) {
	stk->u.num = strtod(stk->u.str, 0);
	stk->op = FLOAT_;
    } else
	UNARY(FLOAT_NEWNODE, strtod(stk->u.str, 0));
}
#endif
