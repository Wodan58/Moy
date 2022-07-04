/*
    module  : sign.c
    version : 1.10
    date    : 06/20/22
*/
#ifndef SIGN_C
#define SIGN_C

/**
sign  :  N1  ->  N2
Integer N2 is the sign (-1 or 0 or +1) of integer N1,
or float N2 is the sign (-1.0 or 0.0 or 1.0) of float N1.
*/
PRIVATE void do_sign(pEnv env)
{
    double dbl;

    ONEPARAM("sign");
    FLOAT("sign");
    if (env->stk->op == FLOAT_) {
	if (env->stk->u.dbl > 0)
	    dbl = 1;
	else if (env->stk->u.dbl < 0)
	    dbl = -1;
	else
	    dbl = 0;
	UNARY(FLOAT_NEWNODE, dbl);
    } else if (env->stk->u.num < 0 || env->stk->u.num > 1)
	UNARY(INTEGER_NEWNODE, env->stk->u.num > 0 ? 1 : -1);
}
#endif
