/*
    module  : enconcat_str.c
    version : 1.2
    date    : 07/10/18
*/
#ifndef ENCONCAT_STR_X
#define ENCONCAT_STR_C

#ifndef SWAPD_C
#undef SWAPD_X
#include "swapd.c"
#define SWAPD_X
#endif

#ifndef CONS_STR_C
#undef CONS_STR_X
#include "cons_str.c"
#define CONS_STR_X
#endif

#ifndef CONCAT_STR_C
#undef CONCAT_STR_X
#include "concat_str.c"
#define CONCAT_STR_X
#endif

#ifdef RUNTIME
void do_enconcat_str(void)
{
    do_swapd();
    do_cons_str();
    do_concat_str();
}
#else
/**
enconcat_str  :  X S T  ->  U
Sequence U is the concatenation of sequences S and T
with X inserted between S and T (== swapd cons concat).
*/
PRIVATE void do_enconcat_str(void)
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
