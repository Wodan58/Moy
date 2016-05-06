/*
    module  : at.c
    version : 1.1
    date    : 04/23/16
*/
#include "interp.h"

/*
at  :  A I  ->  X
X (= A[I]) is the member of A at position I.
*/
/* at.c */
#define PROCEDURE	at_
#define NAME		"at"
#define AGGR		stk->next
#define	INDEX		stk
#include "of_at.c"
