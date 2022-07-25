/*
    module  : __latex_manual.c
    version : 1.7
    date    : 06/20/22
*/
#ifndef __LATEX_MANUAL_C
#define __LATEX_MANUAL_C

#include "manual.h"

/**
__latex_manual  :  ->
Writes this manual of all Joy primitives to output file in Latex style
but without the head and tail.
*/
PRIVATE void do___latex_manual(pEnv env)
{
    COMPILE;
    make_manual(2);
}
/* __latex_manual.c */
#endif
