/*
    module  : strtod.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef STRTOD_X
#define STRTOD_C

#ifdef NEW_RUNTIME
void do_strtod(void)
{
    float dbl;

    TRACE;
    dbl = strtod((char *)stk[-1], 0);
    memcpy(&stk[-1], &dbl, sizeof(node_t));
}
#else
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
    if (OUTSIDE) {
	stk->u.num = strtod(stk->u.str, 0);
	stk->op = FLOAT_;
    } else
	UNARY(FLOAT_NEWNODE, strtod(stk->u.str, 0));
}
#endif
#endif
