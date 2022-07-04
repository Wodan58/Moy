/*
    module  : null.c
    version : 1.13
    date    : 06/20/22
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

    ONEPARAM("null");
    switch (env->stk->op) {
    case ANON_FUNCT_:
	num = !env->stk->u.proc;
	break;
#ifdef COMPILING
    case USR_:
#endif
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
	num = !env->stk->u.num;
	break;
    case SET_:
	num = !env->stk->u.set;
	break;
#ifndef COMPILING
    case USR_:
#endif
    case STRING_:
	num = !*env->stk->u.str;
	break;
    case LIST_:
	num = !env->stk->u.lis;
	break;
    case FLOAT_:
	num = !env->stk->u.dbl;
	break;
    case FILE_:
	num = !env->stk->u.fil;
	break;
    default:
	BADDATA("null");
	break;
    }
    UNARY(BOOLEAN_NEWNODE, num);
}
#endif
