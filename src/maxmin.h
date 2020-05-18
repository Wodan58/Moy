/*
    module  : maxmin.h
    version : 1.8
    date    : 03/28/20
*/
PRIVATE void PROCEDURE(void)
{
#ifndef OLD_RUNTIME
    if (compiling && ((NUMERIC_1 && NUMERIC_2) || (CHAR_1 && CHAR_2)))
	;
    else
	COMPILE;
#endif
    TWOPARAMS(NAME);
#ifndef NCHECK
    if ((((stk->op == FLOAT_ || stk->op == INTEGER_) &&
	  (stk->next->op == FLOAT_ || stk->next->op == INTEGER_)) ||
	  (stk->op == CHAR_ && stk->next->op == CHAR_)));
    else
	execerror("two floats or numerics", NAME);
#endif
    if (stk->next->op == FLOAT_)
	stk->next->u.dbl =
	    FLOATVAL OPER FLOATVAL2 ? FLOATVAL2 : FLOATVAL;
    else if (stk->op == FLOAT_) {
	stk->next->u.dbl =
	    FLOATVAL OPER FLOATVAL2 ? FLOATVAL2 : FLOATVAL;
	stk->next->op = FLOAT_;
    } else
	stk->next->u.num = stk->u.num OPER stk->next->u.num ?
	    stk->next->u.num : stk->u.num;
    POP(stk);
}

#undef PROCEDURE
#undef NAME
#undef OPER
