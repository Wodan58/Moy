/*
    module  : fputstring.c
    version : 1.4
    date    : 06/20/22
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
#endif
