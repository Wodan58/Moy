/*
    module  : fputstring.c
    version : 1.1
    date    : 07/14/18
*/
#ifndef FPUTSTRING_X
#define FPUTSTRING_C

#ifndef FPUTCHARS_C
#undef FPUTCHARS_X
#include "fputchars.c"
#define FPUTCHARS_X
#endif

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
