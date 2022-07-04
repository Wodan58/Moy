/*
    module  : andorxor.h
    version : 1.10
    date    : 06/20/22
*/
PRIVATE void PROCEDURE(pEnv env)
{
    TWOPARAMS(NAME);
    SAME2TYPES(NAME);
    switch (env->stk->op) {
    case SET_:
        BINARY(SET_NEWNODE, env->stk->next->u.set OPER1 env->stk->u.set);
	break;
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
        BINARY(BOOLEAN_NEWNODE, env->stk->next->u.num OPER2 env->stk->u.num);
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
