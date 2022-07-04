/*
    module  : not.c
    version : 1.13
    date    : 06/20/22
*/
#ifndef NOT_C
#define NOT_C

/**
not  :  X  ->  Y
Y is the complement of set X, logical negation for truth values.
*/
PRIVATE void do_not(pEnv env)
{
    ONEPARAM("not");
    switch (env->stk->op) {
    case SET_:
	UNARY(SET_NEWNODE, ~env->stk->u.set);
	break;
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
	UNARY(BOOLEAN_NEWNODE, !env->stk->u.num);
	break;
    default:
	BADDATA("not");
	break;
    }
}
#endif
