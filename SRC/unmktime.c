/* unmktime.c */
PRIVATE void PROCEDURE()
{
    int wday;
    struct tm *t;
    time_t timval;
    Node *cur;

    ONEPARAM(NAME);
    INTEGER(NAME);
    timval = stk->u.num;
    t = FUNC(&timval);
    wday = t->tm_wday;
    if (wday == 0)
	wday = 7;
    cur = newnode(INTEGER_, (Types) wday, 0);
    cur = newnode(INTEGER_, (Types) t->tm_yday, cur);
    cur = newnode(BOOLEAN_, (Types) t->tm_isdst, cur);
    cur = newnode(INTEGER_, (Types) t->tm_sec, cur);
    cur = newnode(INTEGER_, (Types) t->tm_min, cur);
    cur = newnode(INTEGER_, (Types) t->tm_hour, cur);
    cur = newnode(INTEGER_, (Types) t->tm_mday, cur);
    cur = newnode(INTEGER_, (Types) (t->tm_mon + 1), cur);
    cur = newnode(INTEGER_, (Types) (t->tm_year + 1900), cur);
    if (OUTSIDE) {
	stk->u.lis = cur;
	stk->op = LIST_;
    } else
	UNARY(LIST_NEWNODE, cur);
}

#undef PROCEDURE
#undef NAME
#undef FUNC
