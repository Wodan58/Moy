/*
    module  : fold.c
    version : 1.7
    date    : 07/10/18
*/
#ifndef FOLD_X
#define FOLD_C

#ifndef SWAPD_C
#undef SWAPD_X
#include "swapd.c"
#define SWAPD_X
#endif

#ifndef STEP_C
#undef STEP_X
#include "step.c"
#define STEP_X
#endif

#ifdef RUNTIME
void do_fold(void)
{
    do_swapd();
    do_step();
}
#else
/**
fold  :  A V0 [P]  ->  V
Starting with value V0, sequentially pushes members of aggregate A
and combines with binary operator P to produce value V.
*/
PRIVATE void do_fold(void)
{
#ifndef NCHECK
    if (compiling && LIST_1 && VALID_2 && VALID_3)
	;
    else
	COMPILE;
#endif
    THREEPARAMS("fold");
    do_swapd();
    do_step();
}
#endif
#endif
