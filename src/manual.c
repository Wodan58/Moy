/*
    module  : manual.c
    version : 1.7
    date    : 03/05/24
*/
#ifndef MANUAL_C
#define MANUAL_C

#include "manual.h"

/**
Q0  OK  2930  manual  :  N  ->
[IMPURE] Writes this manual of all Joy primitives to output file.
*/
void manual_(pEnv env)
{
    if (env->ignore)
	return;
    make_manual(0);
    /* nothing */
}
#endif
