/*
    module  : 
    version : 1.5
    date    : 03/28/20
*/
#ifndef __LATEX_MANUAL_C
#define __LATEX_MANUAL_C

PRIVATE void make_manual(int style /* 0=plain, 1=HTML, 2=Latex */);

#ifdef MANUAL_X
#undef MANUAL_X
#undef MANUAL_C
#endif

#include "manual.c"

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
