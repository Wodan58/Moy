/*
    module  : plusminus.h
    version : 1.10
    date    : 06/20/22
*/
PRIVATE void PROCEDURE(pEnv env)
{
    TWOPARAMS(NAME);
    TWONUMBERS(NAME);
    if (env->stk->next->op == FLOAT_)
	BINARY(FLOAT_NEWNODE, env->stk->next->u.dbl OPER FLOATVAL);
    else if (env->stk->op == FLOAT_)
	BINARY(FLOAT_NEWNODE, env->stk->next->u.num OPER env->stk->u.dbl);
    else if (env->stk->next->op == CHAR_)
	BINARY(CHAR_NEWNODE, env->stk->next->u.num OPER env->stk->u.num);
    else
	BINARY(INTEGER_NEWNODE, env->stk->next->u.num OPER env->stk->u.num);
}

#undef PROCEDURE
#undef NAME
#undef OPER
