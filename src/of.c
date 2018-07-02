/*
    module  : of.c
    version : 1.4
    date    : 07/02/18
*/

/**
of  :  I A  ->  X
X (= A[I]) is the I-th member of aggregate A.
*/
#define PROCEDURE	do_of
#define NAME		"of"
#define AGGR		stk
#define	INDEX		stk->next
#include "ofat.h"
