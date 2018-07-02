/*
    module  : strtod.c
    version : 1.6
    date    : 07/02/18
*/

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
