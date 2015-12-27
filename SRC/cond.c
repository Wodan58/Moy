/* cond.c */
PRIVATE void cond_()
{
    int num = 0;
    Node *cur, *save;

    ONEPARAM("cond");
/* must check for QUOTES in list */
    LIST("cond");
    CHECKEMPTYLIST(stk->u.lis, "cond");
    cur = stk->u.lis;
    POP(stk);
    save = stk;

    inside_critical++;
    while (cur && cur->next) {
	stk = save;
	exeterm(cur->u.lis->u.lis);
	if ((num = stk->u.num) != 0)
	    break;
	cur = cur->next;
    }
    if (--inside_critical == 0)
	tmp_release();

    stk = save;
    if (num)
	exeterm(cur->u.lis->next);
    else
	exeterm(cur->u.lis);
}
