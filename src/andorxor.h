/*
    module  : andorxor.h
    version : 1.9
    date    : 03/15/21
*/
PRIVATE void PROCEDURE(pEnv env)
{
#ifndef OLD_RUNTIME
    if (compiling && VALID_1 && VALID_2 && env->stk->op == env->stk->next->op &&
	env->stk->op >= BOOLEAN_ && env->stk->op <= SET_)
	;
    else
	COMPILE;
#endif
    TWOPARAMS(NAME);
    SAME2TYPES(NAME);
    switch (env->stk->next->op) {
    case SET_:
	env->stk->next->u.set = env->stk->next->u.set OPER1 env->stk->u.set;
	POP(env->stk);
	break;
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
	env->stk->next->u.num = env->stk->next->u.num OPER2 env->stk->u.num;
	env->stk->next->op = BOOLEAN_;
	POP(env->stk);
	break;
    default:
	BADDATA(NAME);
	break;
    }
}

#undef PROCEDURE
#undef NAME
#undef OPER1
#undef OPER2
