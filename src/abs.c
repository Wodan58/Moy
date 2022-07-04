/*
    module  : abs.c
    version : 1.10
    date    : 06/20/22
*/
#ifndef ABS_C
#define ABS_C

/**
abs  :  N1  ->  N2
Integer N2 is the absolute value (0,1,2..) of integer N1,
or float N2 is the absolute value (0.0 ..) of float N1.
*/
PRIVATE void do_abs(pEnv env)
{
    ONEPARAM("abs");
    FLOAT("abs");
    if (env->stk->op == FLOAT_)
	UNARY(FLOAT_NEWNODE, fabs(env->stk->u.dbl));
    else if (env->stk->u.num < 0)
	UNARY(INTEGER_NEWNODE, -env->stk->u.num);
}
#endif
