/*
    module  : fputstring.c
    version : 1.3
    date    : 03/15/21
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
PRIVATE void do_fputstring(pEnv env)
{
    do_fputchars(env);
}
/* fputchars.c */
#endif
