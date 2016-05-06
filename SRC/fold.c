/*
    module  : fold.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
fold  :  A V0 [P]  ->  V
Starting with value V0, sequentially pushes members of aggregate A
and combines with binary operator P to produce value V.
*/
/* fold.c */
PRIVATE void fold_(void)
{
    THREEPARAMS("fold");
    swapd_();
    step_();
}
