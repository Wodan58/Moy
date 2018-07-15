/*
    module  : localtime.c
    version : 1.6
    date    : 07/15/18
*/
#ifndef LOCALTIME_X
#define LOCALTIME_C

#ifdef NEW_RUNTIME
void do_localtime(void)
{
    int wday;
    struct tm *t;
    time_t timval;
    code_t *root = 0, *cur;

    TRACE;
    timval = stk[-1];
    t = localtime(&timval);
    if ((wday = t->tm_wday) == 0)
	wday = 7;
    cur = joy_code();
    cur->num = wday;
    cur->next = root;
    root = cur;
    cur = joy_code();
    cur->num = t->tm_yday;
    cur->next = root;
    root = cur;
    cur = joy_code();
    cur->num = t->tm_isdst;
    cur->next = root;
    root = cur;
    cur = joy_code();
    cur->num = t->tm_sec;
    cur->next = root;
    root = cur;
    cur = joy_code();
    cur->num = t->tm_min;
    cur->next = root;
    root = cur;
    cur = joy_code();
    cur->num = t->tm_hour;
    cur->next = root;
    root = cur;
    cur = joy_code();
    cur->num = t->tm_mday;
    cur->next = root;
    root = cur;
    cur = joy_code();
    cur->num = t->tm_mon + 1;
    cur->next = root;
    root = cur;
    cur = joy_code();
    cur->num = t->tm_year + 1900;
    cur->next = root;
    root = cur;
    stk[-1] = (node_t)root;
}
#else
/**
localtime  :  I  ->  T
Converts a time I into a list T representing local time:
[year month day hour minute second isdst yearday weekday].
Month is 1 = January ... 12 = December;
isdst is a Boolean flagging daylight savings/summer time;
weekday is 1 = Monday ... 7 = Sunday.
*/
#define PROCEDURE	do_localtime
#define NAME		"localtime"
#define FUNC		localtime
#include "unmktime.h"
#endif
#endif
