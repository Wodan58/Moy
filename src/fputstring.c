/*
    module  : fputstring.c
    version : 1.1
    date    : 07/10/23
*/
#ifndef FPUTSTRING_C
#define FPUTSTRING_C

/**
OK 1980  fputstring  :  DDA	S "abc.."  ->  S
== fputchars, as a temporary alternative.
*/
void fputstring_(pEnv env)
{
    fputchars_(env);
    /* filler */
}
#endif
