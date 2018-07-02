/*
    module  : fold.c
    version : 1.5
    date    : 07/02/18
*/

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
