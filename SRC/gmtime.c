/*
    module  : gmtime.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
gmtime  :  I  ->  T
Converts a time I into a list T representing universal time:
[year month day hour minute second isdst yearday weekday].
Month is 1 = January ... 12 = December;
isdst is false; weekday is 1 = Monday ... 7 = Sunday.
*/
/* gmtime.c */
#define PROCEDURE	gmtime_
#define NAME		"gmtime"
#define FUNC		gmtime
#include "unmktime.c"
