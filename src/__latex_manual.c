/*
    module  : __latex_manual.c
    version : 1.4
    date    : 09/15/23
*/
#ifndef __LATEX_MANUAL_C
#define __LATEX_MANUAL_C

#include "manual.h"

/**
OK 2950  __latex_manual  :  N	->
Writes this manual of all Joy primitives to output file in Latex style
but without the head and tail.
*/
void __latex_manual_(pEnv env)
{
    make_manual(2);
    /* nothing */
}
#endif
