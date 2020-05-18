/*
    module  : abs.c
    version : 1.8
    date    : 03/28/20
*/
#ifndef ABS_C
#define ABS_C

/**
abs  :  N1  ->  N2
Integer N2 is the absolute value (0,1,2..) of integer N1,
or float N2 is the absolute value (0.0 ..) of float N1.
*/
PRIVATE void do_abs(void)
{
#ifndef OLD_RUNTIME
    if (compiling && NUMERIC_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("abs");
    FLOAT("abs");
    if (stk->op == FLOAT_)
	stk->u.dbl = fabs(stk->u.dbl);
    else if (stk->u.num < 0)
	stk->u.num = -stk->u.num;
}
#endif
