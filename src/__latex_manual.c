/*
    module  : __latex_manual.c
    version : 1.4
    date    : 07/15/18
*/
#ifndef __LATEX_MANUAL_X
#define __LATEX_MANUAL_C

#ifdef NEW_RUNTIME
void do___latex_manual(void)
{
    TRACE;
}
#else
PRIVATE void make_manual(int style /* 0=plain, 1=HTML, 2=Latex */);

#ifndef MANUAL_C
#undef MANUAL_X
#include "manual.c"
#define MANUAL_X
#endif

/**
__latex_manual  :  ->
Writes this manual of all Joy primitives to output file in Latex style
but without the head and tail.
*/
PRIVATE void do___latex_manual(void)
{
#ifndef OLD_RUNTIME
    COMPILE;
#endif
    make_manual(2);
}
#endif
#endif
