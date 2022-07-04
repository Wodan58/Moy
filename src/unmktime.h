/*
    module  : unmktime.h
    version : 1.11
    date    : 06/20/22
*/
PRIVATE void PROCEDURE(pEnv env)
{
    static int daynums[] = { 7, 1, 2, 3, 4, 5, 6 };
    Node *cur;
    long wday;
    struct tm t;
    time_t timval;

    ONEPARAM(NAME);
    INTEGER(NAME);
    timval = env->stk->u.num;
    FUNC(&timval, &t);
    wday = daynums[t.tm_wday];
    cur = INTEGER_NEWNODE(wday, 0);
    cur = INTEGER_NEWNODE(t.tm_yday, cur);
    cur = BOOLEAN_NEWNODE(t.tm_isdst, cur);
    cur = INTEGER_NEWNODE(t.tm_sec, cur);
    cur = INTEGER_NEWNODE(t.tm_min, cur);
    cur = INTEGER_NEWNODE(t.tm_hour, cur);
    cur = INTEGER_NEWNODE(t.tm_mday, cur);
    cur = INTEGER_NEWNODE(t.tm_mon + 1, cur);
    cur = INTEGER_NEWNODE(t.tm_year + 1900, cur);
    UNARY(LIST_NEWNODE, cur);
}

#undef PROCEDURE
#undef NAME
#undef FUNC
