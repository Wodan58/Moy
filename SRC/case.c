/* case.c */
PRIVATE void case_()
{
    Node *cur;
    int error;

    TWOPARAMS("case");
    LIST("case");
    cur = stk->u.lis;
    CHECKEMPTYLIST(cur, "case");
    POP(stk);
    for ( ; cur->next; cur = cur->next)
	if (!Compare(cur->u.lis, stk, &error) && !error)
	    break;
    if (cur->next) {
	POP(stk);
	exeterm(cur->u.lis->next);
    } else
	exeterm(cur->u.lis);
}
