/*
    module  : plusminus.h
    version : 1.5
    date    : 07/02/18
*/
PRIVATE void PROCEDURE(void)
{
#ifndef NCHECK
    if (compiling && ((NUMERIC_1 && NUMERIC_2) || (INTEGER_1 && CHAR_2)))
	;
    else
	COMPILE;
#endif
    TWOPARAMS(NAME);
    if (((stk->op == FLOAT_ || stk->op == INTEGER_) &&
	 (stk->next->op == FLOAT_ || stk->next->op == INTEGER_)) ||
	 (stk->op == INTEGER_ && (stk->next->op == CHAR_
			       || stk->next->op == INTEGER_)));
    else
	execerror("two floats or numerics", NAME);
    if (OUTSIDE) {
	if (stk->next->op == FLOAT_)
	    stk->next->u.dbl = stk->next->u.dbl OPER FLOATVAL;
	else if (stk->op == FLOAT_) {
	    stk->next->u.dbl = stk->next->u.num OPER stk->u.dbl;
	    stk->next->op = FLOAT_;
	} else
	    stk->next->u.num = stk->next->u.num OPER stk->u.num;
	POP(stk);
    } else if (stk->next->op == FLOAT_ || stk->op == FLOAT_)
	BINARY(FLOAT_NEWNODE, FLOATVAL2 OPER FLOATVAL);
    else if (stk->next->op == CHAR_)
	BINARY(CHAR_NEWNODE, stk->next->u.num OPER stk->u.num);
    else
	BINARY(INTEGER_NEWNODE, stk->next->u.num OPER stk->u.num);
}

#undef PROCEDURE
#undef NAME
#undef OPER
