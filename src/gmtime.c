/*
    module  : gmtime.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
gmtime  :  I  ->  T
Converts a time I into a list T representing universal time:
[year month day hour minute second isdst yearday weekday].
Month is 1 = January ... 12 = December;
isdst is false; weekday is 1 = Monday ... 7 = Sunday.
*/
#define PROCEDURE	do_gmtime
#define NAME		"gmtime"
#define FUNC		gmtime
#include "unmktime.h"
