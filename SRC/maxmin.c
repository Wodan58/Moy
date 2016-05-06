/*
    module  : maxmin.c
    version : 1.2
    date    : 05/06/16
*/
/* maxmin.c */
PRIVATE void PROCEDURE(void)
{
    TWOPARAMS(NAME);
#ifdef RUNTIME_CHECKS
    if ((((stk->op == FLOAT_ || stk->op == INTEGER_) &&
	  (stk->next->op == FLOAT_ || stk->next->op == INTEGER_)) ||
	  (stk->op == CHAR_ && stk->next->op == CHAR_)));
    else
	execerror("two floats or numerics", NAME);
#endif
    if (OUTSIDE) {
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
    } else if (stk->op == FLOAT_ || stk->next->op == FLOAT_)
	BINARY(FLOAT_NEWNODE,
	       FLOATVAL OPER FLOATVAL2 ? FLOATVAL2 : FLOATVAL);
    else if (stk->op == CHAR_)
	BINARY(CHAR_NEWNODE,
	       stk->u.num OPER stk->next->u.num ?
	       stk->next->u.num : stk->u.num);
    else
	BINARY(INTEGER_NEWNODE,
	       stk->u.num OPER stk->next->u.num ?
	       stk->next->u.num : stk->u.num);
}

#undef PROCEDURE
#undef NAME
#undef OPER
