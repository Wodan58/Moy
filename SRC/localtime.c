/*
    module  : localtime.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
localtime  :  I  ->  T
Converts a time I into a list T representing local time:
[year month day hour minute second isdst yearday weekday].
Month is 1 = January ... 12 = December;
isdst is a Boolean flagging daylight savings/summer time;
weekday is 1 = Monday ... 7 = Sunday.
*/
/* localtime.c */
#define PROCEDURE	localtime_
#define NAME		"localtime"
#define FUNC		localtime
#include "unmktime.c"
