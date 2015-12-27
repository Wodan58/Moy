/* small.c */
PRIVATE void small_()
{
    int small = 0;

    ONEPARAM("small");
    switch (stk->op) {
    case BOOLEAN_:
    case INTEGER_:
	small = stk->u.num < 2;
	break;
    case SET_:
	if (stk->u.set == 0)
	    small = 1;
	else {
	    int i = 0;
	    while (!(stk->u.set & (1 << i)))
		i++;
	    small = (stk->u.set & ~(1 << i)) == 0;
	}
	break;
    case STRING_:
	small = !stk->u.str || stk->u.str[0] == '\0' || stk->u.str[1] == '\0';
	break;
    case LIST_:
	small = stk->u.lis == 0 || stk->u.lis->next == 0;
	break;
    default:
	BADDATA("small");
    }
    if (OUTSIDE) {
	stk->u.num = small;
	stk->op = BOOLEAN_;
    } else
	UNARY(BOOLEAN_NEWNODE, small);
}
