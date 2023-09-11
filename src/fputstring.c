/*
    module  : fputstring.c
    version : 1.4
    date    : 09/11/23
*/
#ifndef FPUTSTRING_C
#define FPUTSTRING_C

/**
OK 1970  fputstring  :  D	S "abc.."  ->  S
== fputchars, as a temporary alternative.
*/
void fputstring_(pEnv env)
{
#ifndef COMPILER
    fputchars_(env);
    /* filler */
#endif
}
#endif
