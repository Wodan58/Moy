/*
    module  : compare.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef COMPARE_C
#define COMPARE_C

/**
compare  :  A B  ->  I
I (=-1,0,+1) is the comparison of aggregates A and B.
The values correspond to the predicates <, =, >.
*/
#define PROCEDURE	do_compare
#define NAME		"compare"
#define CONSTRUCTOR	INTEGER_NEWNODE
#define OPR		+
#define SETCMP		i-j<0?-1:i-j>0
#include "comprel.h"
/* compare.c */
#endif
