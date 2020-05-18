/*
    module  : fputstring.c
    version : 1.2
    date    : 03/28/20
*/
#ifndef FPUTSTRING_C
#define FPUTSTRING_C

#ifdef FPUTCHARS_X
#undef FPUTCHARS_X
#undef FPUTCHARS_C
#endif

#include "fputchars.c"

/**
fputstring  :  S "abc.."  ->  S
== fputchars, as a temporary alternative.
*/
PRIVATE void do_fputstring(void)
{
    do_fputchars();
}
/* fputchars.c */
#endif
