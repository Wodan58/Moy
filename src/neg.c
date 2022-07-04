/*
    module  : neg.c
    version : 1.10
    date    : 06/20/22
*/
#ifndef NEG_C
#define NEG_C

/**
neg  :  I  ->  J
Integer J is the negative of integer I.  Also supports float.
*/
PRIVATE void do_neg(pEnv env)
{
    ONEPARAM("neg");
    FLOAT("neg");
    if (env->stk->op == FLOAT_)
	UNARY(FLOAT_NEWNODE, -env->stk->u.dbl);
    else
	UNARY(INTEGER_NEWNODE, -env->stk->u.num);
}
#endif
