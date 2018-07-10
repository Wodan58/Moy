/*
    module  : unmktime.h
    version : 1.6
    date    : 07/10/18
*/
PRIVATE void PROCEDURE(void)
{
    int wday;
    Node *cur;
    struct tm *t;
    time_t timval;

#ifndef NCHECK
    if (compiling && INTEGER_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM(NAME);
    INTEGER(NAME);
    timval = stk->u.num;
    t = FUNC(&timval);
    wday = t->tm_wday;
    if (wday == 0)
	wday = 7;
    cur = INTEGER_NEWNODE(wday, 0);
    cur = INTEGER_NEWNODE(t->tm_yday, cur);
    cur = BOOLEAN_NEWNODE(t->tm_isdst, cur);
    cur = INTEGER_NEWNODE(t->tm_sec, cur);
    cur = INTEGER_NEWNODE(t->tm_min, cur);
    cur = INTEGER_NEWNODE(t->tm_hour, cur);
    cur = INTEGER_NEWNODE(t->tm_mday, cur);
    cur = INTEGER_NEWNODE(t->tm_mon + 1, cur);
    cur = INTEGER_NEWNODE(t->tm_year + 1900, cur);
    if (OUTSIDE) {
	stk->u.lis = cur;
	stk->op = LIST_;
    } else
	UNARY(LIST_NEWNODE, cur);
}

#undef PROCEDURE
#undef NAME
#undef FUNC
