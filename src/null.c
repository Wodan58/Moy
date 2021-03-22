/*
    module  : null.c
    version : 1.12
    date    : 03/15/21
*/
#ifndef NULL_C
#define NULL_C

/**
null  :  X  ->  B
Tests for empty aggregate X or zero numeric.
*/
PRIVATE void do_null(pEnv env)
{
    int num = 0;

#ifndef OLD_RUNTIME
    if (compiling && VALID_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("null");
    switch (env->stk->op) {
    case STRING_:
	num = !*env->stk->u.str;
	break;
    case FLOAT_:
	num = !env->stk->u.dbl;
	break;
    case FILE_:
	num = !env->stk->u.fil;
	break;
    case LIST_:
	num = !env->stk->u.lis;
	break;
    case SET_:
	num = !env->stk->u.set;
	break;
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
	num = !env->stk->u.num;
	break;
    default:
	BADDATA("null");
	break;
    }
    env->stk->u.num = num;
    env->stk->op = BOOLEAN_;
}
#endif
