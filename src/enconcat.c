/*
    module  : enconcat.c
    version : 1.7
    date    : 07/10/18
*/
#ifndef ENCONCAT_X
#define ENCONCAT_C

#ifndef SWAPD_C
#undef SWAPD_X
#include "swapd.c"
#define SWAPD_X
#endif

#ifndef CONS_C
#undef CONS_X
#include "cons.c"
#define CONS_X
#endif

#ifndef CONCAT_C
#undef CONCAT_X
#include "concat.c"
#define CONCAT_X
#endif

#ifdef RUNTIME
void do_enconcat(void)
{
    do_swapd();
    do_cons();
    do_concat();
}
#else
/**
enconcat  :  X S T  ->  U
Sequence U is the concatenation of sequences S and T
with X inserted between S and T (== swapd cons concat).
*/
PRIVATE void do_enconcat(void)
{
#ifndef NCHECK
    if (compiling && VALID_3 && AGGREGATE_1 && AGGREGATE_2 &&
	stk->op == stk->next->op)
	;
    else
	COMPILE;
#endif
    THREEPARAMS("enconcat");
    SAME2TYPES("enconcat");
    do_swapd();
    do_cons();
    do_concat();
}
#endif
#endif
