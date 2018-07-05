/*
    module  : at.c
    version : 1.5
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_at(void)
{
    int i;
    code_t *cur;

    TRACE;
    for (i = do_pop(), cur = (code_t *)stk[-1]; i > 0; i--)
	cur = cur->next;
    stk[-1] = cur->num;
}
#else
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
