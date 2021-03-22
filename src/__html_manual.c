/*
    module  : __html_manual.c
    version : 1.6
    date    : 03/15/21
*/
#ifndef __HTML_MANUAL_C
#define __HTML_MANUAL_C

PRIVATE void make_manual(int style /* 0=plain, 1=HTML, 2=Latex */);

#ifdef MANUAL_X
#undef MANUAL_X
#undef MANUAL_C
#endif

#include "manual.c"

/**
__html_manual  :  ->
Writes this manual of all Joy primitives to output file in HTML style.
*/
PRIVATE void do___html_manual(pEnv env)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    make_manual(1);
}
#endif
