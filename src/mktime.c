/*
    module  : mktime.c
    version : 1.8
    date    : 07/15/18
*/
#ifndef MKTIME_X
#define MKTIME_C

#ifdef NEW_RUNTIME
void decode_time(struct tm *t)
{
    code_t *cur;

    memset(t, 0, sizeof(struct tm));
    if ((cur = (code_t *)stk[-1])
	return;
    t->tm_year = cur->num - 1900;
    if ((cur = cur->next) == 0)
	return;
    t->tm_mon = cur->num - 1;
    if ((cur = cur->next) == 0)
	return;
    t->tm_mday = cur->num;
    if ((cur = cur->next) == 0)
	return;
    t->tm_hour = cur->num;
    if ((cur = cur->next) == 0)
	return;
    t->tm_min = cur->num;
    if ((cur = cur->next) == 0)
	return;
    t->tm_sec = cur->num;
    if ((cur = cur->next) == 0)
	return;
    t->tm_isdst = cur->num;
    if ((cur = cur->next) == 0)
	return;
    t->tm_yday = cur->num;
    if ((cur = cur->next) == 0)
	return;
    t->tm_wday = cur->num;
}

void do_mktime(void)
{
    struct tm t;

    TRACE;
    decode_time(&t);
    stk[-1] = mktime(&t);
}
#else
PRIVATE void decode_time(struct tm *t)
{
    Node *p;

    memset(t, 0, sizeof(struct tm));
    p = stk->u.lis;
    POP(stk);
    if (p && p->op == INTEGER_) {
	t->tm_year = p->u.num - 1900;
	POP(p);
    }
    if (p && p->op == INTEGER_) {
	t->tm_mon = p->u.num - 1;
	POP(p);
    }
    if (p && p->op == INTEGER_) {
	t->tm_mday = p->u.num;
	POP(p);
    }
    if (p && p->op == INTEGER_) {
	t->tm_hour = p->u.num;
	POP(p);
    }
    if (p && p->op == INTEGER_) {
	t->tm_min = p->u.num;
	POP(p);
    }
    if (p && p->op == INTEGER_) {
	t->tm_sec = p->u.num;
	POP(p);
    }
    if (p && p->op == BOOLEAN_) {
	t->tm_isdst = p->u.num;
	POP(p);
    }
    if (p && p->op == INTEGER_) {
	t->tm_yday = p->u.num;
	POP(p);
    }
    if (p && p->op == INTEGER_) {
	t->tm_wday = p->u.num;
	POP(p);
    }
}

/**
mktime  :  T  ->  I
Converts a list T representing local time into a time I.
T is in the format generated by localtime.
*/
PRIVATE void do_mktime(void)
{
    struct tm t;

#ifndef OLD_RUNTIME
    if (compiling && LIST_1)
	;
    else
	COMPILE;
#endif
    ONEPARAM("mktime");
    LIST("mktime");
    decode_time(&t);
    PUSH(INTEGER_, mktime(&t));
}
#endif
#endif
