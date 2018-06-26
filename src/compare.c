/*
    module  : compare.c
    version : 1.4
    date    : 06/25/18
*/
#include "runtime.h"

/**
compare  :  A B  ->  I
I (=-1,0,+1) is the comparison of aggregates A and B.
The values correspond to the predicates <=, =, >=.
*/
#define PROCEDURE	do_compare
#define NAME		"compare"
#define CONSTRUCTOR	INTEGER_
#define OPR		+
#define SETCMP		i-j<0?-1:i-j>0
#include "comprel.h"