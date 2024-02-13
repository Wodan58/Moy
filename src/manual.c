/*
    module  : manual.c
    version : 1.6
    date    : 02/01/24
*/
#ifndef MANUAL_C
#define MANUAL_C

#include "manual.h"

/**
OK 2930  manual  :  N	->
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
