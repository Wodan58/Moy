/* primrec.c */
PRIVATE void primrec_()
{
    int i, n = 0;
    Node second, third;

    THREEPARAMS("primrec");
    third = *stk->u.lis;
    POP(stk);
    second = *stk->u.lis;
    POP(stk);
    switch (stk->op) {
    case LIST_:
	 {
	    Node *cur;
	    for (cur = stk->u.lis; cur; cur = cur->next, n++)
		DUPLICATE(cur);
	    break;
	}
    case STRING_:
	 {
	    char *str;
	    for (str = stk->u.str; str && *str; str++, n++)
		PUSH(CHAR_, *str);
	    break;
	}
    case SET_:
	 {
	    long_t set = stk->u.set;
	    for (i = 0; i < SETSIZE; i++)
		if (set & (1 << i)) {
		    PUSH(INTEGER_, i);
		    n++;
		}
	    break;
	}
    case INTEGER_:
	 {
	    for (i = stk->u.num; i > 0; i--, n++)
		PUSH(INTEGER_, i);
	    break;
	}
    default:
	BADDATA("primrec");
    }
    exeterm(&second);
    for (i = 0; i < n; i++)
	exeterm(&third);
}
