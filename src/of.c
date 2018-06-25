/*
    module  : of.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
of  :  I A  ->  X
X (= A[I]) is the I-th member of aggregate A.
*/
#define PROCEDURE	do_of
#define NAME		"of"
#define AGGR		stk
#define	INDEX		stk->next
#include "ofat.h"
