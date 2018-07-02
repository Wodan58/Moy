/*
    module  : at.c
    version : 1.4
    date    : 07/02/18
*/

/**
at  :  A I  ->  X
X (= A[I]) is the member of A at position I.
*/
#define PROCEDURE	do_at
#define NAME		"at"
#define AGGR		stk->next
#define	INDEX		stk
#include "ofat.h"
