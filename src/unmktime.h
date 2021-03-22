/*
    module  : unmktime.h
    version : 1.10
    date    : 03/15/21
*/
PRIVATE void PROCEDURE(pEnv env)
{
    Node *cur;
    long_t wday;
    struct tm t;
    time_t timval;

#ifndef OLD_RUNTIME
    if (compiling && INTEGER_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM(NAME);
    INTEGER(NAME);
    timval = env->stk->u.num;
    FUNC(&timval, &t);
    if ((wday = t.tm_wday) == 0)
	wday = 7;
    cur = INTEGER_NEWNODE(wday, 0);
    cur = INTEGER_NEWNODE(t.tm_yday, cur);
    cur = BOOLEAN_NEWNODE(t.tm_isdst, cur);
    cur = INTEGER_NEWNODE(t.tm_sec, cur);
    cur = INTEGER_NEWNODE(t.tm_min, cur);
    cur = INTEGER_NEWNODE(t.tm_hour, cur);
    cur = INTEGER_NEWNODE(t.tm_mday, cur);
    cur = INTEGER_NEWNODE(t.tm_mon + 1, cur);
    cur = INTEGER_NEWNODE(t.tm_year + 1900, cur);
    env->stk->u.lis = cur;
    env->stk->op = LIST_;
}

#undef PROCEDURE
#undef NAME
#undef FUNC
