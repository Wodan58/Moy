/*
    module  : modf.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef MODF_X
#define MODF_C

#ifdef NEW_RUNTIME
void do_modf(void)
{
    node_t temp;
    float dbl, exp;

    TRACE;
    memcpy(&dbl, &stk[-1], sizeof(float));
    dbl = modf(dbl, &exp);
    memcpy(&stk[-1], &dbl, sizeof(node_t));
    memcpy(&temp, &exp, sizeof(node_t));
    do_push(temp);
}
#else
/**
modf  :  F  ->  G H
G is the fractional part and H is the integer part
(but expressed as a float) of F.
*/
PRIVATE void do_modf(void)
{
    double exp;

#ifndef OLD_RUNTIME
    if (compiling && NUMERIC_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("modf");
    FLOAT("modf");
    if (OUTSIDE)
	stk->u.dbl = modf(FLOATVAL, &exp);
    else
	UNARY(FLOAT_NEWNODE, modf(FLOATVAL, &exp));
    DBL_PUSH(exp);
}
#endif
#endif
