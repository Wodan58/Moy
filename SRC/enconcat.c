/*
    module  : enconcat.c
    version : 1.2
    date    : 05/06/16
*/
#include "interp.h"

/*
enconcat  :  X S T  ->  U
Sequence U is the concatenation of sequences S and T
with X inserted between S and T (== swapd cons concat).
*/
/* enconcat.c */
PRIVATE void enconcat_(void)
{
    THREEPARAMS("enconcat");
    SAME2TYPES("enconcat");
    swapd_();
    cons_();
    concat_();
}
