/*
    module  : %M%
    version : %I%
    date    : %G%
*/
#ifdef RUNTIME
void do_fabs(void)
{
    float dbl;

    TRACE;
    memcpy(&dbl, &stk[-1], sizeof(float));
    dbl = fabs(dbl);
    memcpy(&stk[-1], &dbl, sizeof(node_t));
}
#else
/**
fabs  :  N1  ->  N2
Integer N2 is the absolute value (0,1,2..) of integer N1,
or float N2 is the absolute value (0.0 ..) of float N1.
*/
PRIVATE void do_fabs(void)
{
#ifndef NCHECK
    if (compiling && NUMERIC_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("abs");
    FLOAT("abs");
    if (OUTSIDE) {
	if (stk->op == FLOAT_)
	    stk->u.dbl = fabs(stk->u.dbl);
	else if (stk->u.num < 0)
	    stk->u.num = -stk->u.num;
    } else if (stk->op == FLOAT_)
	UNARY(FLOAT_NEWNODE, fabs(stk->u.dbl));
    else if (stk->u.num < 0)
	UNARY(INTEGER_NEWNODE, -stk->u.num);
}
#endif
