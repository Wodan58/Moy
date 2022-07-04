/*
    module  : enconcat.c
    version : 1.11
    date    : 06/20/22
*/
#ifndef ENCONCAT_C
#define ENCONCAT_C

#ifdef SWAPD_X
#undef SWAPD_X
#undef SWAPD_C
#endif

#ifdef CONS_X
#undef CONS_X
#undef CONS_C
#endif

#ifdef CONCAT_X
#undef CONCAT_X
#undef CONCAT_C
#endif

#include "swapd.c"
#include "cons.c"
#include "concat.c"

/**
enconcat  :  X S T  ->  U
Sequence U is the concatenation of sequences S and T
with X inserted between S and T (== swapd cons concat).
*/
PRIVATE void do_enconcat(pEnv env)
{
    THREEPARAMS("enconcat");
    SAME2TYPES("enconcat");
    do_swapd(env);
    do_cons(env);
    do_concat(env);
}
#endif
