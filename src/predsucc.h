/*
    module  : predsucc.h
    version : 1.10
    date    : 06/20/22
*/
PRIVATE void PROCEDURE(pEnv env)
{
    ONEPARAM(NAME);
    NUMERICTYPE(NAME);
    if (env->stk->op == CHAR_)
	UNARY(CHAR_NEWNODE, env->stk->u.num OPER 1);
    else
	UNARY(INTEGER_NEWNODE, env->stk->u.num OPER 1);
}

#undef PROCEDURE
#undef NAME
#undef OPER
