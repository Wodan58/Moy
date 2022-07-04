/*
    module  : decode.h
    version : 1.1
    date    : 06/20/22
*/
#ifndef DECODE_H
#define DECODE_H

PRIVATE void decode_time(pEnv env, struct tm *t)
{
    Node *p;

    memset(t, 0, sizeof(struct tm));
    p = env->stk->u.lis;
    POP(env->stk);
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
	t->tm_wday = p->u.num % 7;
	POP(p);
    }
}
#endif
