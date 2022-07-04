/*
    module  : maxmin.h
    version : 1.10
    date    : 06/20/22
*/
PRIVATE void PROCEDURE(pEnv env)
{
    TWOPARAMS(NAME);
    if (env->stk->next->op == FLOAT_ || env->stk->op == FLOAT_)
	BINARY(FLOAT_NEWNODE, FLOATVAL OPER FLOATVAL2 ? FLOATVAL2 : FLOATVAL);
    else {
	SAME2TYPES(NAME);
	if (env->stk->next->op == CHAR_)
	    BINARY(CHAR_NEWNODE, env->stk->u.num OPER env->stk->next->u.num ?
		env->stk->next->u.num : env->stk->u.num);
	else
	    BINARY(INTEGER_NEWNODE, env->stk->u.num OPER env->stk->next->u.num ?
		env->stk->next->u.num : env->stk->u.num);
    }
}

#undef PROCEDURE
#undef NAME
#undef OPER
