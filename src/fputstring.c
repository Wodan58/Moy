/*
    module  : fputstring.c
    version : 1.2
    date    : 09/04/23
*/
#ifndef FPUTSTRING_C
#define FPUTSTRING_C

/**
OK 1970  fputstring  :  DDA	S "abc.."  ->  S
== fputchars, as a temporary alternative.
*/
void fputstring_(pEnv env)
{
    fputchars_(env);
    /* filler */
}
#endif
