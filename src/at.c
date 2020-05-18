/*
    module  : at.c
    version : 1.8
    date    : 03/28/20
*/
#ifndef AT_C
#define AT_C

/**
at  :  A I  ->  X
X (= A[I]) is the member of A at position I.
*/
#define PROCEDURE	do_at
#define NAME		"at"
#define AGGR		stk->next
#define	INDEX		stk
#include "ofat.h"
#endif
