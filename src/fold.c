/*
    module  : fold.c
    version : 1.6
    date    : 07/05/18
*/
#ifdef RUNTIME
void do_fold(void)
{
    void do_swapd(void), do_step(void);

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
