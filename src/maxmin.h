/*
    module  : maxmin.h
    version : 1.9
    date    : 03/15/21
*/
PRIVATE void PROCEDURE(pEnv env)
{
#ifndef OLD_RUNTIME
    if (compiling && ((NUMERIC_1 && NUMERIC_2) || (CHAR_1 && CHAR_2)))
	;
    else
	COMPILE;
#endif
    TWOPARAMS(NAME);
#ifndef NCHECK
    if ((((env->stk->op == FLOAT_ || env->stk->op == INTEGER_) &&
	  (env->stk->next->op == FLOAT_ || env->stk->next->op == INTEGER_)) ||
	  (env->stk->op == CHAR_ && env->stk->next->op == CHAR_)));
    else
	execerror("two floats or numerics", NAME);
#endif
    if (env->stk->next->op == FLOAT_)
	env->stk->next->u.dbl =
	    FLOATVAL OPER FLOATVAL2 ? FLOATVAL2 : FLOATVAL;
    else if (env->stk->op == FLOAT_) {
	env->stk->next->u.dbl =
	    FLOATVAL OPER FLOATVAL2 ? FLOATVAL2 : FLOATVAL;
	env->stk->next->op = FLOAT_;
    } else
	env->stk->next->u.num = env->stk->u.num OPER env->stk->next->u.num ?
	    env->stk->next->u.num : env->stk->u.num;
    POP(env->stk);
}

#undef PROCEDURE
#undef NAME
#undef OPER
