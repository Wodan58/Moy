/*
    module  : fputstring.c
    version : 1.7
    date    : 02/01/24
*/
#ifndef FPUTSTRING_C
#define FPUTSTRING_C

/**
OK 1970  fputstring  :  D	S "abc.."  ->  S
[FOREIGN] == fputchars, as a temporary alternative.
*/
void fputstring_(pEnv env)
{
    fputchars_(env);
    /* nothing */
}
#endif
