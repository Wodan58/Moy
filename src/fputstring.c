/*
    module  : fputstring.c
    version : 1.5
    date    : 09/15/23
*/
#ifndef FPUTSTRING_C
#define FPUTSTRING_C

/**
OK 1970  fputstring  :  D	S "abc.."  ->  S
== fputchars, as a temporary alternative.
*/
void fputstring_(pEnv env)
{
    fputchars_(env);
    /* nothing */
}
#endif
