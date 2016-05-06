/*
    module  : decode.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/* decode.c */
PRIVATE void decode_time(struct tm *t)
{
    Node *p;

    t->tm_year = t->tm_mon = t->tm_mday =
	t->tm_hour = t->tm_min = t->tm_sec = t->tm_isdst =
	t->tm_yday = t->tm_wday = 0;
    p = stk->u.lis;
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
