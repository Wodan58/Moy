/*
    module  : localtime.c
    version : 1.10
    date    : 03/15/21
*/
#ifndef LOCALTIME_C
#define LOCALTIME_C

#ifdef _MSC_VER
void localtime_r(time_t *t, struct tm *tm)
{
    *tm = *localtime(t);
}
#endif

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
#define FUNC		localtime_r
#include "unmktime.h"
#endif
