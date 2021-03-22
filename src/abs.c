/*
    module  : abs.c
    version : 1.9
    date    : 03/15/21
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
#ifndef OLD_RUNTIME
    if (compiling && NUMERIC_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("abs");
    FLOAT("abs");
    if (env->stk->op == FLOAT_)
	env->stk->u.dbl = fabs(env->stk->u.dbl);
    else if (env->stk->u.num < 0)
	env->stk->u.num = -env->stk->u.num;
}
#endif
