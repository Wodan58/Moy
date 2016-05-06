/*
    module  : of.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
of  :  I A  ->  X
X (= A[I]) is the I-th member of aggregate A.
*/
/* of.c */
#define PROCEDURE	of_
#define NAME		"of"
#define AGGR		stk
#define	INDEX		stk->next
#include "of_at.c"
