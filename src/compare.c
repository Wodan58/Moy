/*
    module  : compare.c
    version : 1.5
    date    : 07/02/18
*/

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
