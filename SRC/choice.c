/* choice.c */
PRIVATE void choice_()
{
    THREEPARAMS("choice");
    if (OUTSIDE) {
	if (stk->next->next->u.num) {
	    stk->next->next->u = stk->next->u;
	    stk->next->next->op = stk->next->op;
	} else {
	    stk->next->next->u = stk->u;
	    stk->next->next->op = stk->op;
	}
	POP(stk);
	POP(stk);
    } else if (stk->next->next->u.num)
	stk = newnode(stk->next->op, stk->next->u, stk->next->next->next);
    else
	stk = newnode(stk->op, stk->u, stk->next->next->next);
}
