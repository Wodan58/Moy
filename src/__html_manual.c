/*
    module  : __html_manual.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef __HTML_MANUAL_C
#define __HTML_MANUAL_C

#include "manual.h"

/**
Q0  OK  2940  __html_manual  :  N  ->
[IMPURE] Writes this manual of all Joy primitives to output file in HTML style.
*/
void __html_manual_(pEnv env)
{
    if (env->ignore)
	return;
    make_manual(1);
    /* nothing */
}
#endif
