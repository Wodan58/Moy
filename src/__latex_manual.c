/*
    module  : __latex_manual.c
    version : 1.6
    date    : 02/01/24
*/
#ifndef __LATEX_MANUAL_C
#define __LATEX_MANUAL_C

#include "manual.h"

/**
OK 2950  __latex_manual  :  N	->
[IMPURE] Writes this manual of all Joy primitives to output file in Latex style
but without the head and tail.
*/
void __latex_manual_(pEnv env)
{
    if (env->ignore)
	return;
    make_manual(2);
    /* nothing */
}
#endif
